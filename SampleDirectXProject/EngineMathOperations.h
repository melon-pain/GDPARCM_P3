#pragma once
#include <cmath>

class EngineMathOperations
{
public:
	static float FMod(float X, float Y)
	{
		const float AbsY = std::abs(Y);
		if (AbsY <= 1.e-8f)
		{
			return 0.0f;
		}

		// Convert to double for better precision, since intermediate rounding can lose enough precision to skew the result.
		const auto DX = static_cast<double>(X);
		const auto DY = static_cast<double>(Y);

		const double Div = (DX / DY);
		const double IntPortion = DY * trunc(Div);
		const double Result = DX - IntPortion;
		// Convert back to float. This is safe because the result will by definition not exceed the X input.
		return static_cast<float>(Result);
	}

	static void	SinCos(float* sin, float* cos, float value)
	{
		*sin = std::sinf(value);
		*cos = std::cosf(value);
	}

	static float ClampAxis(float angle)
	{
		angle = FMod(angle, 360.0f);

		if (angle < 0.0f)
		{
			// shift to [0,360) range
			angle += 360.0f;
		}

		return angle;
	}

	static float NormalizeAxis(float angle)
	{
		angle = ClampAxis(angle);

		if (angle > 180.0f)
		{
			// shift to (-180,180]
			angle -= 360.0f;
		}

		return angle;
	}
};