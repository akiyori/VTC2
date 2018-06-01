#pragma once

#include <chrono>
#include <iostream>
#include "spdlog/spdlog.h"

namespace detail
{
	namespace chrono
	{
		template<typename P>
		struct UnitName;

#define DEF_UNIT_NAME(T, N) \
        template<> struct UnitName<std::chrono::T> { static constexpr const char *name = #N; }

		DEF_UNIT_NAME(hours, h);
		DEF_UNIT_NAME(minutes, m);
		DEF_UNIT_NAME(seconds, s);
		DEF_UNIT_NAME(milliseconds, ms);
		DEF_UNIT_NAME(microseconds, us);

#undef DEF_UNIT_NAME
	}
}

template<typename Prec>
class StopWatch final
{
	using time_point = std::chrono::time_point<std::chrono::system_clock>;

private:
	time_point start_;

	void start()
	{
		start_ = std::chrono::system_clock::now();
	}
public:
	StopWatch()
	{
		start();
	}

	~StopWatch()
	{
		const time_point end = std::chrono::system_clock::now();
		auto time = std::chrono::duration_cast<Prec>(end - start_).count();
		auto unit = detail::chrono::UnitName<Prec>::name;
		auto logger = spdlog::get("async_file_logger");
		logger->info("elapsed time: {} [{}]", time, unit);
	}
};