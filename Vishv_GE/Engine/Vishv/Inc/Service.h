#ifndef INCLUDED_VISHV_SERVICES_SERVICE_H
#define INCLUDED_VISHV_SERVICES_SERVICE_H

namespace Vishv
{
	class GameWorld;

	class Service
	{
	public:
		META_CLASS_DECLARE

		Service() = default;
		virtual ~Service() {}
		
		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update() {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const { return *mWorld; }

		const std::string & GetTypeID() const { return mTypeID; }
		void DoUI(void* instance, const Core::Meta::MetaClass& mclass);

	protected:
		void SetName(std::string&& name) { mTypeID = std::move(name); }

	private:
		friend class GameWorld;

		GameWorld* mWorld = nullptr;

		std::string mTypeID;
	};
}

#endif // !INCLUDED_VISHV_SERVICES_SERVICE_H



