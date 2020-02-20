#ifndef INCLUDED_VISHV_GRAPHICS_ANIMATIONEASING
#define INCLUDED_VISHV_GRAPHICS_ANIMATIONEASING

namespace Vishv::Graphics
{
	/* refernece https://easings.net/en */

	enum class EasingType
	{
		none = -1,

		InSine,
		OutSine,
		InOutSine,
		InQuad,
		OutQuad,
		InOutQuad,
		InCubic,
		OutCubic,
		InOutCubic,
		InQuart,
		OutQuart,
		InOutQuart,
		InQuint,
		OutQuint,
		InOutQuint,
		InExpo,
		OutExpo,
		InOutExpo,
		InCirc,
		OutCirc,
		InOutCirc,
		InBack,
		OutBack,
		InOutBack,

		
		InElastic,			//need to implement
		OutElastic,			//need to implement
		InOutElastic,		//need to implement
		InBounce,			//need to implement
		OutBounce,			//need to implement
		InOutBounce			//need to implement
	};

	enum class EasingHead
	{
		none = -1,
		Sine,
		Quad,
		Cubic,
		Quart,
		Quint,
		Expo,
		Circ,
		Back,

		Elastic, //need to implement
		Bounce, //need to implement

	};

	class EaseCalculation
	{
	public:
		static std::string ToString(Vishv::Graphics::EasingHead type);

		static float GetTime(float time, EasingHead head, bool isIn);
		static float GetTime(float time, EasingType type);		//Send in time and the type and it will use internal function to find out right answer

	private:
		static float InSine(float time);
		static float OutSine(float time);
		static float InOutSine(float time);

		static float InQuad(float time);
		static float OutQuad(float time);
		static float InOutQuad(float time);

		static float InCubic(float time);
		static float OutCubic(float time);
		static float InOutCubic(float time);

		static float InQuart(float time);
		static float OutQuart(float time);
		static float InOutQuart(float time);

		static float InQuint(float time);
		static float OutQuint(float time);
		static float InOutQuint(float time);

		static float InExpo(float time);
		static float OutExpo(float time);
		static float InOutExpo(float time);

		static float InCirc(float time);
		static float OutCirc(float time);
		static float InOutCirc(float time);

		static float InBack(float time);
		static float OutBack(float time);
		static float InOutBack(float time);


		/*These have to implemented*/
		static float InElastic(float time);
		static float OutElastic(float time);
		static float InOutElastic(float time);

		static float InBounce(float time);
		static float OutBounce(float time);
		static float InOutBounce(float time);

	};

}

#endif // !INCLUDED_VISHV_GRAPHICS_ANIMATIONEASING
