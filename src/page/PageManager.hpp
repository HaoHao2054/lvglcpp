#pragma once
#include "IPage.hpp"
#include <map>
#include <string>

namespace ui {

class PageManager {
private:
    PageManager() = default;
    IPage* m_current_page = nullptr;
    std::map<std::string, IPage*> m_page_map;

public:
    PageManager(const PageManager&) = delete;
    PageManager& operator=(const PageManager&) = delete;

    static PageManager& instance();

    /// @brief 注册一个页面实例
    void registerPage(IPage* page);

    /// @brief 切换到指定名称的页面
    void switchToPage(const std::string& name);
};

} // namespace ui