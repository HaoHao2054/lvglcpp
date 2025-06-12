// file: PageSelector.cpp (优化后)
#include "PageSelector.hpp"
#include "PageManager.hpp" // 在.cpp文件中包含，以调用PageManager的方法

namespace ui {

    // 静态的C风格“跳板”函数
    static void event_roller_cb_trampoline(lv_event_t *e) {
        PageSelector* self = static_cast<PageSelector*>(lv_event_get_user_data(e)); // 把用户数据转换为 PageSelector 指针
        if (self) {
            // 调用真正的成员函数来处理事件
            self->on_roller_value_changed(e);
        }
    }

    PageSelector &PageSelector::instance() {
        static PageSelector selector;
        return selector;
    }

    PageSelector::PageSelector() {
        // 创建在顶层，确保不被页面覆盖
        m_roller = lv_roller_create(lv_layer_top());

        lv_roller_set_visible_row_count(m_roller, 4);
        lv_obj_set_width(m_roller, 150);
        lv_obj_center(m_roller);

        // 注册事件回调，并将'this'指针作为用户数据传递
        lv_obj_add_event_cb(m_roller, event_roller_cb_trampoline, LV_EVENT_VALUE_CHANGED, this);

        // 默认隐藏
        lv_obj_add_flag(m_roller, LV_OBJ_FLAG_HIDDEN);
    }

    PageSelector::~PageSelector() {
        if (m_roller && lv_obj_is_valid(m_roller)) {
            lv_obj_del(m_roller);
        }
    }

    void PageSelector::syncWithPageManager() {
        // 1. 从 PageManager 获取页面名称列表
        auto page_names = PageManager::instance().getRegisteredPageNames();

        // 2. 构建 LVGL roller 所需的选项字符串 (以 '\n' 分隔)
        std::string options;
        for (const auto &name: page_names) {
            if (!options.empty()) {
                options += "\n";
            }
            options += name;
        }

        // 3. 设置 roller 的选项
        if (m_roller) {
            lv_roller_set_options(m_roller, options.c_str(), LV_ROLLER_MODE_NORMAL);
        }
    }

    void PageSelector::on_roller_value_changed(lv_event_t *e) {
        if (!m_roller)
            return;

        char buf[64]; // 缓冲区要足够大
        lv_roller_get_selected_str(m_roller, buf, sizeof(buf));

        // 4. 获取到选中的页面名称后，通知 PageManager 进行切换
        PageManager::instance().switchToPage(buf);
    }

    void PageSelector::align(lv_align_t align, int x_ofs, int y_ofs) {
        if (m_roller) {
            lv_obj_align(m_roller, align, x_ofs, y_ofs);
        }
    }

    void PageSelector::show() {
        if (m_roller) {
            lv_obj_clear_flag(m_roller, LV_OBJ_FLAG_HIDDEN);
            lv_obj_move_foreground(m_roller); // 确保在最顶层
        }
    }

    void PageSelector::hide() {
        if (m_roller) {
            lv_obj_add_flag(m_roller, LV_OBJ_FLAG_HIDDEN);
        }
    }

} // namespace ui
