#include "Precompiled.h"
#include "Common.h"
#include "AnimationEasing.h"


namespace 
{
	Vishv::Math::Vector2 Lerp(Vishv::Math::Vector2 p0, Vishv::Math::Vector2 p1, float t)
	{
		VISHVASSERT(t >= 0.0f && t <= 1.0f, "[Lerping] invalid t value");
		return (p0 * (1.0f - t)) + (p1 * t);
	}
	
	float CubicBezier(float t, Vishv::Math::Vector2 p1, Vishv::Math::Vector2 p2)
	{
		Vishv::Math::Vector2 pStart(0.0f, 0.0f);
		Vishv::Math::Vector2 pEnd(1.0f, 1.0f);
	
		auto P(Lerp(pStart, p1, t));
		auto Q(Lerp(p1, p2, t));
		auto R(Lerp(p2, pEnd, t));
		auto S(Lerp(P, Q, t));
		auto T(Lerp(Q, R, t));
	
		return Lerp(S, T, t).y;
	}
}



std::string Vishv::Graphics::EaseCalculation::ToString(Vishv::Graphics::EasingHead type)
{
	switch (type)
	{
	case Vishv::Graphics::EasingHead::none:
		return "none";
		break;
	case Vishv::Graphics::EasingHead::Sine:
		return "Sine";
		break;
	case Vishv::Graphics::EasingHead::Quad:
		return "Quad";
		break;
	case Vishv::Graphics::EasingHead::Cubic:
		return "Cubic";
		break;
	case Vishv::Graphics::EasingHead::Quart:
		return "Quart";
		break;
	case Vishv::Graphics::EasingHead::Quint:
		return "Quint";
		break;
	case Vishv::Graphics::EasingHead::Expo:
		return "Expo";
		break;
	case Vishv::Graphics::EasingHead::Circ:
		return "Circ";
		break;
	case Vishv::Graphics::EasingHead::Back:
		return "Back";
		break;
	case Vishv::Graphics::EasingHead::Elastic:
		return "Elastic";
		break;
	case Vishv::Graphics::EasingHead::Bounce:
		return "Bounce";
		break;
	default:
		break;
	}
	return std::string();
}

float Vishv::Graphics::EaseCalculation::GetTime(float time, EasingHead head, bool isIn)
{
	EasingType type = EasingType::none;

	switch (head)
	{
	case EasingHead::Sine:
		type = isIn ? EasingType::InSine : EasingType::OutSine;
	case Vishv::Graphics::EasingHead::Quad:
		type = isIn ? EasingType::InQuad : EasingType::OutQuad;
		break;
	case Vishv::Graphics::EasingHead::Cubic:
		type = isIn ? EasingType::InCubic : EasingType::OutCubic;
		break;
	case Vishv::Graphics::EasingHead::Quart:
		type = isIn ? EasingType::InQuart : EasingType::OutQuart;
		break;
	case Vishv::Graphics::EasingHead::Quint:
		type = isIn ? EasingType::InQuint : EasingType::OutQuint;
		break;
	case Vishv::Graphics::EasingHead::Expo:
		type = isIn ? EasingType::InExpo : EasingType::OutExpo;
		break;
	case Vishv::Graphics::EasingHead::Circ:
		type = isIn ? EasingType::InCirc : EasingType::OutCirc;
		break;
	case Vishv::Graphics::EasingHead::Back:
		type = isIn ? EasingType::InBack : EasingType::OutBack;
		break;
	case Vishv::Graphics::EasingHead::Elastic:
		type = isIn ? EasingType::InElastic : EasingType::OutElastic;
		break;
	case Vishv::Graphics::EasingHead::Bounce:
		type = isIn ? EasingType::InBounce : EasingType::OutBounce;
		break;
	default:
		return time;
		break;
	}

	return GetTime(time, type);
}

float Vishv::Graphics::EaseCalculation::GetTime(float time, EasingType type)
{
	switch (type)
	{
	case EasingType::InSine:
		return InSine(time);
		break;
	case EasingType::OutSine:
		return OutSine(time);
		break;
	case EasingType::InOutSine:
		return InOutSine(time);
		break;
	case EasingType::InQuad:
		return InQuad(time);
		break;
	case EasingType::OutQuad:
		return OutQuad(time);
		break;
	case EasingType::InOutQuad:
		return InOutQuad(time);
		break;
	case EasingType::InCubic:
		return InCubic(time);
		break;
	case EasingType::OutCubic:
		return OutCubic(time);
		break;
	case EasingType::InOutCubic:
		return InOutCubic(time);
		break;
	case EasingType::InQuart:
		return InQuart(time);
		break;
	case EasingType::OutQuart:
		return OutQuart(time);
		break;
	case EasingType::InOutQuart:
		return InOutQuart(time);
		break;
	case EasingType::InQuint:
		return InQuint(time);
		break;
	case EasingType::OutQuint:
		return OutQuint(time);
		break;
	case EasingType::InOutQuint:
		return InOutQuint(time);
		break;
	case EasingType::InExpo:
		return InExpo(time);
		break;
	case EasingType::OutExpo:
		return OutExpo(time);
		break;
	case EasingType::InOutExpo:
		return InOutExpo(time);
		break;
	case EasingType::InCirc:
		return InCirc(time);
		break;
	case EasingType::OutCirc:
		return OutCirc(time);
		break;
	case EasingType::InOutCirc:
		return InOutCirc(time);
		break;
	case EasingType::InBack:
		return InBack(time);
		break;
	case EasingType::OutBack:
		return OutBack(time);
		break;
	case EasingType::InOutBack:
		return InOutBack(time);
		break;
	case EasingType::InElastic:
		return InElastic(time);
		break;
	case EasingType::OutElastic:
		return OutElastic(time);
		break;
	case EasingType::InOutElastic:
		return InOutElastic(time);
		break;
	case EasingType::InBounce:
		return InBounce(time);
		break;
	case EasingType::OutBounce:
		return OutBounce(time);
		break;
	case EasingType::InOutBounce:
		return InOutBounce(time);
		break;
	default:
		return time;
	}
}


float Vishv::Graphics::EaseCalculation::InSine(float time)
{
	return CubicBezier(time, { 0.47f ,0.0f }, { 0.745f, 0.715f });
}
float Vishv::Graphics::EaseCalculation::OutSine(float time)
{
	return CubicBezier(time, { 0.39f ,0.575f }, { 0.565f, 1.0f });
}
float Vishv::Graphics::EaseCalculation::InOutSine(float time)
{
	return CubicBezier(time, { 0.445f ,0.05f }, { 0.55f, 0.95f });
}


float Vishv::Graphics::EaseCalculation::InQuad(float time)
{
	return CubicBezier(time, { 0.55f ,0.085f }, { 0.68f, 0.53f });
}
float Vishv::Graphics::EaseCalculation::OutQuad(float time)
{
	return CubicBezier(time, { 0.25f ,0.46f }, { 0.45f, 0.94f });
}
float Vishv::Graphics::EaseCalculation::InOutQuad(float time)
{
	return CubicBezier(time, { 0.455f ,0.03f }, { 0.515f, 0.955f });
}


float Vishv::Graphics::EaseCalculation::InCubic(float time)
{
	return CubicBezier(time, { 0.55f ,0.055f }, { 0.675f, 0.19f });
}
float Vishv::Graphics::EaseCalculation::OutCubic(float time)
{
	return CubicBezier(time, { 0.215f ,0.61f }, { 0.355f, 1.0f });
}
float Vishv::Graphics::EaseCalculation::InOutCubic(float time)
{
	return CubicBezier(time, { 0.645f ,0.045f }, { 0.355f, 1.0f });
}


float Vishv::Graphics::EaseCalculation::InQuart(float time)
{
	return CubicBezier(time, { 0.895f ,0.03f }, { 0.685f, 0.22f });
}
float Vishv::Graphics::EaseCalculation::OutQuart(float time)
{
	return CubicBezier(time, { 0.165f ,0.84f }, { 0.44f, 1.0f });
}
float Vishv::Graphics::EaseCalculation::InOutQuart(float time)
{
	return CubicBezier(time, { 0.77f ,0.0f }, { 0.175f, 1.0f });
}


float Vishv::Graphics::EaseCalculation::InQuint(float time)
{
	return CubicBezier(time, { 0.755f ,0.05f }, { 0.855f, 0.06f });
}
float Vishv::Graphics::EaseCalculation::OutQuint(float time)
{
	return CubicBezier(time, { 0.23f ,1.0f }, { 0.32f, 1.0f });
}
float Vishv::Graphics::EaseCalculation::InOutQuint(float time)
{
	return CubicBezier(time, { 0.86f ,0.f }, { 0.07f, 1.f });
}


float Vishv::Graphics::EaseCalculation::InExpo(float time)
{
	return CubicBezier(time, { 0.95f ,0.05f }, { 0.795f, 0.035f });
}
float Vishv::Graphics::EaseCalculation::OutExpo(float time)
{
	return CubicBezier(time, { 0.19f ,1.f }, { 0.22f, 1.f });
}
float Vishv::Graphics::EaseCalculation::InOutExpo(float time)
{
	return CubicBezier(time, { 1.f ,0.f }, { 0.f, 1.f });
}


float Vishv::Graphics::EaseCalculation::InCirc(float time)
{
	return CubicBezier(time, { 0.6f ,0.04f }, { 0.98f, 0.335f });
}
float Vishv::Graphics::EaseCalculation::OutCirc(float time)
{
	return CubicBezier(time, { 0.075f ,0.82f }, { 0.165f, 1.f });
}
float Vishv::Graphics::EaseCalculation::InOutCirc(float time)
{
	return CubicBezier(time, { 0.785f ,0.135f }, { 0.5f, 0.86f });
}


float Vishv::Graphics::EaseCalculation::InBack(float time)
{
	return CubicBezier(time, { 0.6f ,-0.28f }, { 0.735f, 0.045f });
}
float Vishv::Graphics::EaseCalculation::OutBack(float time)
{
	return CubicBezier(time, { 0.175f ,0.885f }, { 0.32f, 1.275f });
}
float Vishv::Graphics::EaseCalculation::InOutBack(float time)
{
	return CubicBezier(time, { 0.68f ,-0.55f }, { 0.265f, 1.55f });
}

float Vishv::Graphics::EaseCalculation::InElastic(float time)
{
	return time;
}
float Vishv::Graphics::EaseCalculation::OutElastic(float time)
{
	return time;
}
float Vishv::Graphics::EaseCalculation::InOutElastic(float time)
{
	return time;
}


float Vishv::Graphics::EaseCalculation::InBounce(float time)
{
	return time;
}
float Vishv::Graphics::EaseCalculation::OutBounce(float time)
{
	return time;
}
float Vishv::Graphics::EaseCalculation::InOutBounce(float time)
{
	return time;
}
