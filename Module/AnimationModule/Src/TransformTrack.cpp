#include "TransformTrack.h"

bool TransformTrack::IsValid()
{
    return position_.Size() > 1 || rotate_.Size() > 1 || scale_.Size() > 1;
}

float TransformTrack::GetStartTime()
{
    float time = 0.0f;
    bool bIsSet = false;

    if (position_.Size() > 1)
    {
        time = position_.GetStartTime();
        bIsSet = true;
    }

    if (rotate_.Size() > 1)
    {
        float rotationStartTime = rotate_.GetStartTime();
        if (rotationStartTime < time || !bIsSet)
        {
            time = rotationStartTime;
            bIsSet = true;
        }
    }

    if (scale_.Size() > 1)
    {
        float scaleStartTime = scale_.GetStartTime();
        if (scaleStartTime < time || !bIsSet)
        {
            time = scaleStartTime;
            bIsSet = true;
        }
    }

    return time;
}

float TransformTrack::GetEndTime()
{
    float time = 0.0f;
    bool bIsSet = false;

    if (position_.Size() > 1)
    {
        time = position_.GetEndTime();
        bIsSet = true;
    }

    if (rotate_.Size() > 1)
    {
        float rotationEndTime = rotate_.GetEndTime();
        if (rotationEndTime > time || !bIsSet)
        {
            time = rotationEndTime;
            bIsSet = true;
        }
    }

    if (scale_.Size() > 1)
    {
        float scaleEndTime = scale_.GetEndTime();
        if (scaleEndTime > time || !bIsSet)
        {
            time = scaleEndTime;
            bIsSet = true;
        }
    }

    return time;
}
