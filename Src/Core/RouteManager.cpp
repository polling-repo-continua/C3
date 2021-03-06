#include "StdAfx.h"
#include "RouteManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FSecure::C3::Core::RouteManager::Route::Route(RouteId routeId, std::shared_ptr<DeviceBridge> const& iface)
	: m_RouteId(routeId)
	, m_Channel(iface)
	, m_OutgoingDeviceId(iface->GetDid())
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<FSecure::C3::Core::RouteManager::Route> FSecure::C3::Core::RouteManager::FindRoute(RouteId const& routeId) const noexcept
{
	return m_Routes.Find([&routeId](std::shared_ptr<Route> const& c) { return c->m_RouteId == routeId; });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<FSecure::C3::Core::RouteManager::Route> FSecure::C3::Core::RouteManager::FindRoute(AgentId const& agentId) const noexcept
{
	return m_Routes.Find([&agentId](std::shared_ptr<Route> const& c) { return c->m_RouteId.GetAgentId() == agentId; });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<FSecure::C3::Core::RouteManager::Route> FSecure::C3::Core::RouteManager::AddRoute(RouteId routeId, std::shared_ptr<DeviceBridge> channel)
{
	return m_Routes.TryAdd([&routeId](std::shared_ptr<Route> const& c) { return c->m_RouteId == routeId; }, std::make_shared<Route>(routeId, channel));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FSecure::C3::Core::RouteManager::RemoveRoute(RouteId const& routeId)
{
	m_Routes.Remove([&routeId](std::shared_ptr<Route> const& c) { return c->m_RouteId == routeId; });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<FSecure::C3::Core::RouteManager::Route> FSecure::C3::Core::RouteManager::FindRouteByOutgoingChannel(DeviceId deviceId) const noexcept
{
	return m_Routes.Find([&deviceId](auto const& e) {return e->m_OutgoingDeviceId == deviceId; });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FSecure::C3::Core::RouteManager::RemoveAllRoutes()
{
	m_Routes.Clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FSecure::C3::Core::RouteManager::RemoveChannelRoutes(DeviceId outgoingDeviceId)
{
	m_Routes.RemoveIf( [outgoingDeviceId](auto& route) { return route->m_OutgoingDeviceId == outgoingDeviceId; });
}
