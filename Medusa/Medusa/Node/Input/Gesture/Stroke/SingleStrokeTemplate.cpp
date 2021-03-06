// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "SingleStrokeTemplate.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SingleStrokeTemplate::SingleStrokeTemplate()
{
	//SIREN_BODY_CONSTRUCT_BEGIN
	mBeginAngle = 0.f;
	//SIREN_BODY_CONSTRUCT_END
}

SingleStrokeTemplate::~SingleStrokeTemplate()
{
	//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}


void SingleStrokeTemplate::AddLine(const Line2F& line, uint sampleCount)
{
	mPath.AddRange(line.SampleWithoutBeginEnd(sampleCount));
}

void SingleStrokeTemplate::AddLine(const Point2F& from, const Point2F& to, uint sampleCount)
{
	Line2F line(from, to);
	mPath.AddRange(line.SampleWithoutBeginEnd(sampleCount));
}

void SingleStrokeTemplate::AddLine(float fromX, float fromY, float toX, float toY, uint sampleCount)
{
	AddLine(mpp(fromX, fromY), mpp(toX, toY), sampleCount);
}

void SingleStrokeTemplate::BeginAdd(float fromX, float fromY)
{
	mCurrentAddPoint.X = fromX;
	mCurrentAddPoint.Y = fromY;
}

void SingleStrokeTemplate::BeginAdd(const Point2F& pos)
{
	mCurrentAddPoint = pos;
}

void SingleStrokeTemplate::AddTo(float toX, float toY, uint sampleCount)
{
	AddLine(mCurrentAddPoint, mpp(toX, toY), sampleCount);
	mCurrentAddPoint.X = toX;
	mCurrentAddPoint.Y = toY;
}

void SingleStrokeTemplate::AddTo(const Point2F& pos, uint sampleCount)
{
	AddLine(mCurrentAddPoint, pos, sampleCount);
	mCurrentAddPoint = pos;
}

void SingleStrokeTemplate::Clear()
{
	mPath.Clear();
	mStartUnitVector = Point2F::Zero;
	mVectors.Clear();
	mBeginAngle = 0.f;
	mBeginScale = 0.f;
}

SingleStrokeTemplate* SingleStrokeTemplate::Clone() const
{
	SingleStrokeTemplate* copy = new SingleStrokeTemplate();
	copy->SetName(mName);
	copy->MutablePath() = mPath;
	copy->SetStartUnitVector(mStartUnitVector);
	copy->CalculateVectors();

	copy->SetBeginAngle(mBeginAngle);
	copy->SetBeginScale(mBeginScale);
	return copy;
}

void SingleStrokeTemplate::Train(const SingleStrokeTemplate& val,float scale)
{
	//val is already normalized
	//we just simplify average the two
	auto count = mPath.Points().Count();
	if (count==0)
	{
		mPath = val.mPath;
		mStartUnitVector = val.mStartUnitVector;
		CalculateVectors();
		mBeginAngle = val.mBeginAngle;
		mBeginScale = val.mBeginScale*scale;
	}

	Log::AssertFormat(count == val.Path().Points().Count(), "Should have the same point count");
	FOR_EACH_SIZE(i, count)
	{
		auto& self = mPath.MutablePoints()[i];
		const auto& other = val.Path().Points()[i];
		self = (self + other) / 2.f;
	}
}

void SingleStrokeTemplate::Normalize(size_t strokePointCount, float squareSize, bool ignoreRotation)
{
	/* Recognition algorithm from
	http://faculty.washington.edu/wobbrock/pubs/uist-07.1.pdf
	Step 1: Resample the Point Path
	Step 2: Rotate Once Based on the "Indicative Angle"
	Step 3: Scale and Translate
	Step 4: Find the Optimal Angle for the Best Score
	*/
	// TODO: Switch to $N algorithm so can handle 1D shapes

	// Make everyone have the same number of points (anchor points)
	mPath = mPath.Resample((uint)strokePointCount);
	// Pretend that all gestures began moving from right hand side
	//  (degree 0). Makes matching two items easier if they're
	//  rotated the same
	if (!ignoreRotation)
	{
		mBeginAngle = mPath.IndicativeAngle();
		mPath.RotateToOrigin();
	}
	// Pretend all shapes are the same size. 
	// Note that since this is a square, our new shape probably
	//  won't be the same aspect ratio
	Scale2F scale;
	auto boudingBox = mPath.BoundingBox();
	scale.X = squareSize / boudingBox.Size.Width;
	scale.Y = squareSize / boudingBox.Size.Height;
	mBeginScale = scale;
	mPath.Scale(scale);
	// Move the shape until its center is at 0,0 so that everyone
	//  is in the same coordinate system
	mPath.TranslateToOrigin();


	CalculateVectors();
}


void SingleStrokeTemplate::CalculateVectors()
{
	mVectors = mPath;
	mVectors.Vectorize();
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(SingleStrokeTemplate, 20);
SIREN_FIELD_METADATA_STRUCT(0, SingleStrokeTemplate, Name, 4);
SIREN_FIELD_METADATA_STRUCT(1, SingleStrokeTemplate, Path, 4);
SIREN_FIELD_METADATA(2, SingleStrokeTemplate, BeginAngle, 10, 0.f, false);
SIREN_FIELD_METADATA_STRUCT(3, SingleStrokeTemplate, BeginScale, 10);
//SIREN_BODY_METADATA_END

MEDUSA_END;