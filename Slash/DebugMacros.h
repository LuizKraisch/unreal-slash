#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_DEBUG_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12.f, FColor::Magenta, true);
#define DRAW_DEBUG_SPHERE_SINGLE_FRAME(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12.f, FColor::Magenta, false, -1.f);
#define DRAW_DEBUG_LINE(Start, End) if (GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1.f, 0, 1.f);
#define DRAW_DEBUG_LINE_SINGLE_FRAME(Start, End) if (GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1.f, 0, 1.f);
#define DRAW_DEBUG_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 25.f, FColor::Blue, true);
#define DRAW_DEBUG_POINT_SINGLE_FRAME(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 25.f, FColor::Blue, false, -1.f);
#define DRAW_DEBUG_VECTOR(Start, End) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), End, 25.f, FColor::Blue, true); \
	}
#define DRAW_DEBUG_VECTOR_SINGLE_FRAME(Start, End) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), End, 25.f, FColor::Blue, false, -1.f); \
	}