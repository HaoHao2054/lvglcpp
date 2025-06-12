#include "HomePage.hpp"
#include "PageManager.hpp" // 用于页面切换

namespace ui {

HomePage& HomePage::instance() {
    static HomePage page;
    return page;
}

void HomePage::initWidgets() {
    if (m_is_initialized) return; // 防止重复初始化

    // 1. 创建根容器
    m_root_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(m_root_container, LV_PCT(100), LV_PCT(100));
    lv_obj_clear_flag(m_root_container, LV_OBJ_FLAG_SCROLLABLE);

    // 2. 在根容器上创建此页面的所有控件
    m_title_label = lv_label_create(m_root_container);
    lv_label_set_text(m_title_label, "Welcome Home");
    lv_obj_align(m_title_label, LV_ALIGN_TOP_MID, 0, 20);

    m_info_label = lv_label_create(m_root_container);
    lv_label_set_text(m_info_label, "This is the home page.");
    lv_obj_center(m_info_label);

    m_settings_button = lv_btn_create(m_root_container);
    lv_obj_align(m_settings_button, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(m_settings_button, on_settings_button_clicked, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* btn_label = lv_label_create(m_settings_button);
    lv_label_set_text(btn_label, "Settings");
    lv_obj_center(btn_label);

    m_is_initialized = true;
}

void HomePage::destroyWidgets() {
    if (!m_is_initialized) return;

    // RAII的核心体现：只删除根容器，LVGL会负责级联删除所有子控件
    if (m_root_container && lv_obj_is_valid(m_root_container)) {
        lv_obj_del(m_root_container);
    }
    // 将所有指针置空，状态复位
    m_root_container = nullptr;
    m_title_label = nullptr;
    m_info_label = nullptr;
    m_settings_button = nullptr;
    m_is_initialized = false;
}

void HomePage::on_settings_button_clicked(lv_event_t* e) {
    // 通过PageManager切换到设置页面
    PageManager::instance().switchToPage("SettingsPage");
}

} // namespace ui