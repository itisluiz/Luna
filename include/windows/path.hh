#ifndef LUNA_WINDOWS_PATH_HH
#define LUNA_WINDOWS_PATH_HH
#include <filesystem>
#include <fstream>
#include <string>
#include <optional>

namespace fs = std::filesystem;

std::wstring sanitizePathComponent(std::wstring pathComponent, bool checkBadNames = false);
std::string sanitizePathComponent(std::string pathComponent, bool checkBadNames = false);
fs::path sanitizePath(fs::path path);
fs::path sanitizePath(fs::path path, std::string ext);
std::optional<fs::path> getAppdata(const fs::path& subPath = { });
std::ofstream saveFile(fs::path path, std::ios_base::openmode openMode = 0);
std::ifstream openFile(fs::path path);

#endif