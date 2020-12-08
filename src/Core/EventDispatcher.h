#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

namespace Three
{
	class EventDispatcher
	{
	public:
		typedef std::shared_ptr<std::function<void(const void* const)>> FunctionSharedPtr;
	public:
		EventDispatcher();
		bool AddEventListener(const std::string& type, const FunctionSharedPtr& listener);
		bool HasEventListener(const std::string& type, const FunctionSharedPtr& listener);
		bool RemoveEventListener(const std::string& type, const FunctionSharedPtr& listener);
		void DispatchEvent(const std::string& type, const void* const param);
	private:
		 std::unordered_map<std::string, std::unordered_set<FunctionSharedPtr>> mListeners;
	};
} // namespace Three
