#pragma once
#include "IPage.hpp"

namespace ui {

class HomePage : public IPage {
private:
    // 私有构造函数，防止外部直接创建实例
    HomePage() = default;

    // --- 此页面特有的控件句柄 ---
    lv_obj_t* m_title_label = nullptr;
    lv_obj_t* m_info_label = nullptr;
    lv_obj_t* m_settings_button = nullptr;

public:
    // 禁止拷贝和赋值
    HomePage(const HomePage&) = delete;
    HomePage& operator=(const HomePage&) = delete;

    // 获取单例实例的静态方法
    static HomePage& instance();

    // --- 实现基类的纯虚函数 ---
    const char* getName() const override { return "HomePage"; }
    void initWidgets() override;
    void destroyWidgets() override;

private:
    // 私有的事件回调等
    static void on_settings_button_clicked(lv_event_t* e);
};

} // namespace ui