#include "EventDispatcher.h"

namespace Three
{
    using namespace std;
	
	EventDispatcher::EventDispatcher()
	{
	}

	bool EventDispatcher::AddEventListener(const std::string& type, const FunctionSharedPtr& listener)
	{
		if (HasEventListener(type, listener))
		{
			return false;
		}

		auto _ls = mListeners.find(type);
		if (mListeners.end() == _ls)
		{
			mListeners[type] = unordered_set<FunctionSharedPtr>();
			_ls = mListeners.find(type);
		}
		_ls->second.insert(listener);
		return true;
	}

	bool EventDispatcher::HasEventListener(const std::string& type, const FunctionSharedPtr& listener)
	{
		const auto _ls = mListeners.find(type);
		if (mListeners.end() == _ls)
		{
			return false;
		}
		else
		{
			return _ls->second.end() == _ls->second.find(listener);
		}
	}

	bool EventDispatcher::RemoveEventListener(const std::string& type, const FunctionSharedPtr& listener)
	{
		if (!HasEventListener(type, listener))
		{
			return false;
		}
		mListeners.find(type)->second.erase(listener);
		return true;
	}

	void EventDispatcher::DispatchEvent(const std::string& type, const void* const param)
	{
		const auto _ls = mListeners.find(type);
		if (mListeners.end() == _ls)
		{
			return;
		}
		else
		{
			for (const auto& _l : _ls->second)
			{
				(*_l)(param);
			}
		}
	}
}