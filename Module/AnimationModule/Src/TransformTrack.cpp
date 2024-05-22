#include "TransformTrack.h"

bool TransformTrack::IsValid()
{
    return position_.Size() > 1 || rotate_.Size() > 1 || scale_.Size() > 1;
}
