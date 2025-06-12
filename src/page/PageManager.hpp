#pragma once
#include "IPage.hpp"
#include <map>
#include <string>
#include <vector>

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

    /**
     * @brief 获取所有已注册页面的名称列表。
     * @return 一个包含所有页面名称的 std::vector<std::string>。
     */
    std::vector<std::string> getRegisteredPageNames() const;
};

} // namespace ui