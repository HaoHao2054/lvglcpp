#include "LabeledSlider.hpp"

LabeledSlider::LabeledSlider(lv_obj_t *parent) {
    m_container = lv_obj_create(parent);
    lv_obj_set_size(m_container, 250, 80); // 组件的默认大小
    lv_obj_clear_flag(m_container, LV_OBJ_FLAG_SCROLLABLE);

    m_title_label = lv_label_create(m_container);
    lv_label_set_text(m_title_label, "Slider");
    lv_obj_align(m_title_label, LV_ALIGN_TOP_LEFT, 0, 0);

    m_slider = lv_slider_create(m_container);
    lv_obj_set_width(m_slider, 200);
    lv_obj_align(m_slider, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_add_event_cb(m_slider, on_slider_event, LV_EVENT_VALUE_CHANGED, this);

    m_value_label = lv_label_create(m_container);
    lv_label_set_text(m_value_label, "0");
    lv_obj_align_to(m_value_label, m_slider, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
}

LabeledSlider::~LabeledSlider() {
    // 因为所有控件都是m_container的子对象，
    // 所以只需要删除m_container，LVGL就会自动清理所有内部控件
    if (m_container && lv_obj_is_valid(m_container)) {
        lv_obj_del(m_container);
    }
}

void LabeledSlider::on_slider_event(lv_event_t *e) {
    LabeledSlider *self = static_cast<LabeledSlider *>(lv_event_get_user_data(e));
    if (self) {
        int value = lv_slider_get_value(self->m_slider);
        lv_label_set_text_fmt(self->m_value_label, "%d", value);
        if (self->m_value_changed_callback) {
            self->m_value_changed_callback(value);
        }
    }
}

void LabeledSlider::onValueChanged(std::function<void(int)> callback) {
    m_value_changed_callback = std::move(callback);
}

void LabeledSlider::setTitle(const std::string &title) { lv_label_set_text(m_title_label, title.c_str()); }

void LabeledSlider::align(lv_align_t align, int x_ofs, int y_ofs) { lv_obj_align(m_container, align, x_ofs, y_ofs); }
