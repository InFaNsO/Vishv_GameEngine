#ifndef INCLUDED_VISHV_COMPONENT_H
#define INCLUDED_VISHV_COMPONENT_H

class Vishv::GameObject;

namespace Vishv::Components
{
	class Component
	{
	public:
		META_CLASS_DECLARE

		virtual ~Component() = default;

		virtual void Initialize() {}
		virtual void Update() {}
		virtual void SimpleDraw() {}
		virtual void DebugUI() {}
		virtual void Render() {}
		virtual void Terminate() {}

		GameObject& GetOwner();
		const GameObject& GetOwner() const;
	private:
		friend class GameObject;
		using Components = std::vector<std::unique_ptr<Component>>;

		GameObject * mOwner = nullptr;
		Components mComponents;

	};
}


#endif // !INCLUDED_VISHV_COMPONENT_H


