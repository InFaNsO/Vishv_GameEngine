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

		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const { return *mWorld; }

		const std::string & GetTypeID() const { return mTypeID; }

	private:
		friend class GameWorld;

		GameWorld* mWorld = nullptr;

		std::string mTypeID;
	};
}

#endif // !INCLUDED_VISHV_SERVICES_SERVICE_H



