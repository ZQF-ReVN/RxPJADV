#pragma once
#include <vector>
#include <string>
#include <string_view>


namespace ZQF::ReVN::RxPJADV::Script
{
	class FileNameDat
	{
	private:
		std::vector<std::string> m_vcName;

	public:
		FileNameDat();
		FileNameDat(const std::string_view msFileNameBinPath, const std::size_t nCodePage);

	public:
		auto Load(const std::string_view msFileNameBinPath, const std::size_t nCodePage) -> void;

	public:
		auto operator[](std::size_t nIndex) -> const std::string&;
	};
} // namespace ZQF::ReVN::RxPJADV::Script