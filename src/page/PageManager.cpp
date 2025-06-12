#include "PageManager.hpp"
#include <iostream>

namespace ui {

    PageManager &PageManager::instance() {
        static PageManager manager;
        return manager;
    }

    void PageManager::registerPage(IPage *page) {
        if (page) {
            m_page_map[page->getName()] = page;
        }
    }

    void PageManager::switchToPage(const std::string &name) {
        auto it = m_page_map.find(name);
        if (it == m_page_map.end()) {
            std::cerr << "PageManager: Page '" << name << "' not found!" << std::endl;
            return; // 找不到页面
        }

        IPage *new_page = it->second;

        // 隐藏当前页面（如果存在）
        if (m_current_page) {
            m_current_page->hide();
        }

        // 显示新页面
        new_page->initWidgets(); // 确保控件已创建
        new_page->show();

        // 如果你想用LVGL的屏幕加载动画，可以在这里调用
        // lv_scr_load_anim(new_page->getRoot(), LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);

        m_current_page = new_page;
    }

    std::vector<std::string> PageManager::getRegisteredPageNames() const {
        std::vector<std::string> names;
        names.reserve(m_page_map.size()); // 预分配内存提高效率
        for (const auto &pair: m_page_map) {
            names.push_back(pair.first);
        }
        return names;
    }

} // namespace ui
