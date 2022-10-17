// Copyright (c) 2011 The Foundry Visionmongers Ltd.  All Rights Reserved.

#include "DDImage/DeepFilterOp.h"
#include "DDImage/Knobs.h"
#include "DDImage/Row.h"

#include <stdio.h>

static const char *CLASS = "DeepCKeymix";
static const char *HELP = "A Keymix node to use withing a deep stream. Mimics the 2d KeyMix node in controls and behavior.\n\n"
                          "Falk Hofmann 12/2021";

using namespace DD::Image;

static const char *const bbox_names[] = {"union", "B\tB side", "A\tA side", nullptr};

class DeepCKeymix : public DeepFilterOp
{
    ChannelSet _processChannelSet;
    Channel maskChannel;
    bool invertMask;
    float mix;

    enum
    {
        UNION,
        BBOX,
        ABOX
    };
    int bbox_type;

protected:
    Iop *_maskOp;
    DeepOp *_aOp;
    DeepOp *_bOp;
    bool _bypass;

public:
    DeepCKeymix(Node *node) : DeepFilterOp(node)
    {
        inputs(3);

        _processChannelSet = Mask_All;
        maskChannel = Chan_Alpha;
        invertMask = _bypass = false;
        mix = 1;
        bbox_type = UNION;
    }

    const char *node_help() const override { return HELP; }
    const char *Class() const override { return CLASS; }
    virtual Op *op() override { return this; }

    bool test_input(int input, Op *op) const
    {
        switch (input)
        {
        case 0:
        case 1:
            return DeepFilterOp::test_input(input, op); // Deep A and B Input
        case 2:
            return dynamic_cast<Iop *>(op) != 0;    // Mask Input
        default:
            return DeepFilterOp::test_input(input, op);
        }
    }

    const char* input_label(int n, char *) const override
    {
        switch (n)
        {
        case 0: return "B";
        case 1:  return "A";
        default: return "mask";
        }
    }

    void knobs(Knob_Callback f) override
    {
        Input_ChannelMask_knob(f, &_processChannelSet, 1, "channels");
        Tooltip(f, "Channels to include into the KeyMix.");
        Input_Channel_knob(f, &maskChannel, 1, 2, "mask_channel", "mask channel");
        Tooltip(f, "Channel to use from mask input");
        Bool_knob(f, &invertMask, "invertMask", "invert");
        Tooltip(f, "Flip meaning of the the mask channel");
        Float_knob(f, &mix, "mix");
        Tooltip(f, "Dissolve between B-only at 0 and the full keymix at 1");
        Enumeration_knob(f, &bbox_type, bbox_names, "bbox", "Set BBox to");
        Tooltip(f, "Clip one input to match the other if wanted");
    }

    void _validate(bool for_real) override
    {
        _bypass = _processChannelSet.size() == 0 ? true : false;

        _aOp = dynamic_cast<DeepOp *>(Op::input(1));
        _bOp = input0();
        _maskOp = dynamic_cast<Iop *>(Op::input(2));

        if ((!_aOp) || (!_maskOp))
            _bypass = true;

        if (_bOp != nullptr)
        {
            if (_aOp != nullptr && _maskOp != nullptr)
            {
                _aOp->validate(for_real);
                _bOp->validate(for_real);
                _maskOp->validate(for_real);

                DeepInfo infoA = _aOp->deepInfo();
                DeepInfo infoB = _bOp->deepInfo();

                switch (bbox_type)
                {
                case UNION:
                    infoB.merge(infoA);
                    _deepInfo = infoB;
                    break;
                case ABOX:
                    _deepInfo = infoA;
                    break;
                case BBOX:
                    _deepInfo = infoB;
                    break;
                default:
                    _deepInfo = infoB;
                    break;
                }
            }
            else
            {
                _deepInfo = _bOp->deepInfo();
            }
        }
        else
        {
            DeepFilterOp::_validate(for_real);
        }
    }

    void getDeepRequests(Box box, const ChannelSet &channels, int count, std::vector<RequestData> &requests) override
    {
        if (!input0())
            return;

        ChannelSet requestChannels = _processChannelSet;
        requests.push_back(RequestData(input0(), box, requestChannels, count));

        if (_aOp != nullptr)
        {
            requests.push_back(RequestData(_aOp, box, requestChannels, count));
        }
        if (_maskOp != nullptr)
        {
            _maskOp->request(box, maskChannel, count);
        }
    }

    bool doDeepEngine(DD::Image::Box box, const ChannelSet& requestedChannels, DeepOutputPlane& plane) override
    {

        ChannelSet process = requestedChannels;
        process += _processChannelSet;

        if (!_bOp)
            return true;

        DeepPlane bPlane;
        if (!_bOp->deepEngine(box, process, bPlane))
            return false;

        DeepInPlaceOutputPlane outPlane(process, box);
        outPlane.reserveSamples(bPlane.getTotalSampleCount());
        if (_bypass)
        {
            for (Box::iterator it = box.begin(), itEnd = box.end(); it != itEnd; ++it)
            {
                DeepPixel bPixel = bPlane.getPixel(it);
                size_t inPixelSamples = bPixel.getSampleCount();
                outPlane.setSampleCount(it, inPixelSamples);
                DeepOutputPixel outPixel = outPlane.getPixel(it);
                size_t outSample = 0;
                for (size_t sampleNo = 0; sampleNo < inPixelSamples; sampleNo++)
                {
                    const float *inData = bPixel.getUnorderedSample(sampleNo);
                    float *outData = outPixel.getWritableUnorderedSample(outSample);
                    for (int iChannel = 0, nChannels = requestedChannels.size();
                         iChannel < nChannels;
                         ++iChannel, ++outData, ++inData)
                    {
                        *outData = *inData;
                    }
                    ++outSample;
                }
            }
        }
        else
        {
            DeepPlane aPlane;
            if (!_aOp->deepEngine(box, process, aPlane))
                return false;

            float maskVal = 0.0f;     
            Row maskRow(box.x(), box.r());

            _maskOp->get(box.y(), box.x(), box.r(), maskChannel, maskRow);
            int currentYRow = box.y();
    
            for (Box::iterator it = box.begin(), itEnd = box.end(); it != itEnd; ++it)
            {
                if (currentYRow != it.y)
                {
                    _maskOp->get(it.y, box.x(), box.r(), maskChannel, maskRow);
                    maskVal = maskRow[maskChannel][it.x];
                    maskVal = clamp(maskVal, 0.0f, 1.0f);
                    currentYRow = it.y;
                }
                else
                {
                    maskVal = clamp(maskRow[maskChannel][it.x], 0.0f, 1.0f);
                }

                if (invertMask)
                {
                    maskVal = 1.0f - maskVal;
                }

                DeepPixel aPixel = aPlane.getPixel(it);
                DeepPixel bPixel = bPlane.getPixel(it);

                size_t inPixelSamples = 0;
                size_t aSampleNo = aPixel.getSampleCount();
                size_t bSampleNo = bPixel.getSampleCount();

                float mixing = maskVal * mix;

                if (maskVal <= 0.0f || mix <= 0.0f)
                {
                    inPixelSamples = bSampleNo;
                }
                else if (mixing >= 1.0f)
                {
                    inPixelSamples = aSampleNo;
                }
                else if (mix > 0.0f)
                {
                    inPixelSamples = bSampleNo + aSampleNo;
                }

                outPlane.setSampleCount(it, inPixelSamples);

                DeepOutputPixel outPixel = outPlane.getPixel(it);
                ChannelSet aInPixelChannels = bPixel.channels();
                ChannelSet bInPixelChannels = bPixel.channels();
                
                for (size_t sampleNo = 0; sampleNo < inPixelSamples; sampleNo++)
                {
                    foreach (z, process)
                    {
                        float &outData = outPixel.getWritableUnorderedSample(sampleNo, z);

                        if (maskVal <= 0.0f || mix <= 0.0f)
                        {
                            outData = bPixel.getUnorderedSample(sampleNo, z);
                        }
                        else if (mixing >= 1.0f)
                        {
                            outData = aPixel.getUnorderedSample(sampleNo, z);
                        }
                        else
                        {
                            if ((z == Chan_DeepFront) || (z == Chan_DeepBack)) {
                                continue;
                            }

                            if (sampleNo < bSampleNo)
                            {   
                                
                                float bInData = bInPixelChannels.contains(z)
                                              ? bPixel.getUnorderedSample(sampleNo, z)
                                              : 0.0f;

                                outData = (1.0f - mixing) * bInData; 
                            }
                            else
                            {
                                float aInData = aInPixelChannels.contains(z)
                                                ? aPixel.getUnorderedSample(sampleNo - bSampleNo, z)
                                                           : 0.0f;

                                outData = aInData * mixing;
                            }  
                        }   

                    }
                }
            }
        }

        outPlane.reviseSamples();
        mFnAssert(outPlane.isComplete());
        plane = outPlane;

        return true;
    }

    static const Description d;
};

static Op *build(Node *node) { return new DeepCKeymix(node); }
const Op::Description DeepCKeymix::d(::CLASS, 0, build);
