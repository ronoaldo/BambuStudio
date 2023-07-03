#ifndef slic3r_CreatePresetsDialog_hpp_
#define slic3r_CreatePresetsDialog_hpp_

#include "libslic3r/Preset.hpp"
#include "wxExtensions.hpp"
#include "GUI_Utils.hpp"
#include "Widgets/Label.hpp"
#include "Widgets/TextInput.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/RadioBox.hpp"
#include "Widgets/CheckBox.hpp"
#include "Widgets/ComboBox.hpp"

namespace Slic3r { 
namespace GUI {

class CreateFilamentPresetDialog : public DPIDialog
{
public:
    CreateFilamentPresetDialog(wxWindow *parent);
    ~CreateFilamentPresetDialog();

protected:
    enum FilamentOptionType { 
        VENDOR = 0,
        TYPE,
        SERIAL,
        FILAMENT_PRESET,
        PRESET_FOR_PRINTER,
        FILAMENT_NAME_COUNT
    };

protected:
    void on_dpi_changed(const wxRect &suggested_rect) override;
    wxBoxSizer *create_item(FilamentOptionType option_type);
    wxBoxSizer *create_vendor_item();
    wxBoxSizer *create_type_item();
    wxBoxSizer *create_serial_item();
    wxBoxSizer *create_filament_preset_item();
    wxBoxSizer *create_filament_preset_for_printer_item();
    wxBoxSizer *create_button_item();

private:
    void          clear_filament_preset_map();
    wxArrayString get_filament_preset_choices();
    wxBoxSizer *  create_radio_item(wxString title, wxWindow *parent, wxString tooltip, std::vector<std::pair<RadioBox *, wxString>> &radiobox_list);
    void          select_curr_radiobox(std::vector<std::pair<RadioBox *, wxString>> &radiobox_list, int btn_idx);
    wxString      curr_create_filament_type();
    void          get_filament_presets_by_machine();
    void          get_all_filament_presets();

private:
    struct CreateType
    {
        wxString base_filament;
        wxString base_filament_preset;
    };

private:
    std::vector<std::pair<RadioBox *, wxString>>              m_create_type_btns;
    std::vector<std::pair<CheckBox *, Preset *>>              m_filament_preset;
    std::unordered_map<CheckBox *, Preset *>                  m_machint_filament_preset;
    std::unordered_map<std::string, std::vector<Preset *>>    m_filament_choice_map;
    std::unordered_map<std::string, std::string>              m_public_name_to_filament_id_map;
    std::unordered_map<std::string, Preset *>                 m_all_presets_map;
    CreateType                                                m_create_type;
    Button *                                                  m_button_create                = nullptr;
    Button *                                                  m_button_cancel                = nullptr;
    ComboBox *                                                m_filament_vendor_combobox     = nullptr;
    ComboBox *                                                m_filament_type_combobox       = nullptr;
    ComboBox *                                                m_exist_vendor_combobox        = nullptr;
    ComboBox *                                                m_filament_preset_combobox     = nullptr;
    TextInput *                                               m_filament_custom_vendor_input = nullptr;
    wxGridSizer *                                             m_filament_presets_sizer       = nullptr;
    wxPanel *                                                 m_filament_preset_panel        = nullptr;
    TextInput *                                               m_filament_serial_input        = nullptr;

};

class CreatePrinterPresetDialog : public DPIDialog
{
public:
    CreatePrinterPresetDialog(wxWindow *parent);
    ~CreatePrinterPresetDialog();

protected:
    void on_dpi_changed(const wxRect &suggested_rect) override;

/********************************************************    Control Construction    *****************************************************/
    wxBoxSizer *create_step_switch_item();
    //Create Printer Page1
    void        create_printer_page1(wxWindow *parent);
    wxBoxSizer *create_type_item(wxWindow *parent);
    wxBoxSizer *create_printer_item(wxWindow *parent);
    wxBoxSizer *create_nozzle_diameter_item(wxWindow *parent);
    wxBoxSizer *create_bed_shape_item(wxWindow *parent);
    wxBoxSizer *create_bed_size_item(wxWindow *parent);
    wxBoxSizer *create_origin_item(wxWindow *parent);
    wxBoxSizer *create_hot_bed_stl_item(wxWindow *parent);
    wxBoxSizer *create_hot_bed_svg_item(wxWindow *parent);
    wxBoxSizer *create_max_print_height_item(wxWindow *parent);
    wxBoxSizer *create_page1_btns_item(wxWindow *parent);
    void        load_texture();
    void        load_model_stl();
    //Improt Presets Page2
    void create_printer_page2(wxWindow *parent);
    wxBoxSizer *create_printer_preset_item(wxWindow *parent);
    wxBoxSizer *create_presets_item(wxWindow *parent);
    wxBoxSizer *create_presets_template_item(wxWindow *parent);
    wxBoxSizer *create_page2_btns_item(wxWindow *parent);

    void show_page1();
    void show_page2();

/**********************************************************    Data Interaction    *******************************************************/
    bool          data_init();
    void          select_curr_radiobox(std::vector<std::pair<RadioBox *, wxString>> &radiobox_list, int btn_idx);
    void          select_all_preset_template(std::vector<std::pair<CheckBox *, Preset *>> &preset_templates);
    void          deselect_all_preset_template(std::vector<std::pair<CheckBox *, Preset *>> &preset_templates);
    void          update_presets_list();
    void          on_preset_model_value_change(wxCommandEvent &e);
    void          clear_preset_combobox();
    bool          save_printable_area_config(Preset *preset);
    bool          validate_input_valid();
    wxArrayString printer_preset_sort_with_nozzle_diameter(const VendorProfile &vendor_profile, float nozzle_diameter);

    wxBoxSizer *create_radio_item(wxString title, wxWindow *parent, wxString tooltip, std::vector<std::pair<RadioBox *, wxString>> &radiobox_list);

    wxString    curr_create_preset_type();
    wxString    curr_create_printer_type();

private:
    std::vector<std::pair<RadioBox *, wxString>>       m_create_type_btns;
    std::vector<std::pair<RadioBox *, wxString>>       m_create_presets_btns;
    std::vector<std::pair<CheckBox *, Preset *>>       m_filament_preset;
    std::vector<std::pair<CheckBox *, Preset *>>       m_process_preset;
    std::vector<wxString>                              m_create_printer_type;
    std::vector<wxString>                              m_create_presets_type;
    VendorProfile                                      m_printer_preset_vendor_selected;
    Slic3r::VendorProfile::PrinterModel                m_printer_preset_model_selected;
    bool                                               rewritten                        = false;
    Preset *                                           m_printer_preset                 = nullptr;
    wxStaticBitmap *                                   m_step_1                         = nullptr;
    wxStaticBitmap *                                   m_step_2                         = nullptr;
    Button *                                           m_button_OK                      = nullptr;
    Button *                                           m_button_create                  = nullptr;
    Button *                                           m_button_page1_cancel            = nullptr;
    Button *                                           m_button_page2_cancel            = nullptr;
    Button *                                           m_button_page2_back              = nullptr;
    Button *                                           m_button_bed_stl                 = nullptr;
    Button *                                           m_button_bed_svg                 = nullptr;
    wxWindow *                                         m_page1                          = nullptr;
    wxWindow *                                         m_page2                          = nullptr;
    ComboBox *                                         m_select_vendor                  = nullptr;
    ComboBox *                                         m_select_model                   = nullptr;
    ComboBox *                                         m_select_printer                 = nullptr;
    CheckBox *                                         m_can_not_find_vendor_combox     = nullptr;
    wxStaticText *                                     m_can_not_find_vendor_text       = nullptr;
    wxTextCtrl *                                       m_custom_vendor_model            = nullptr;
    ComboBox *                                         m_nozzle_diameter                = nullptr;
    ComboBox *                                         m_printer_vendor                 = nullptr;
    ComboBox *                                         m_printer_model                  = nullptr;
    TextInput *                                        m_bed_size_x_input               = nullptr;
    TextInput *                                        m_bed_size_y_input               = nullptr;
    TextInput *                                        m_bed_origin_x_input             = nullptr;
    TextInput *                                        m_bed_origin_y_input             = nullptr;
    TextInput *                                        m_print_height_input             = nullptr;
    wxGridSizer *                                      m_filament_preset_template_sizer = nullptr;
    wxGridSizer *                                      m_process_preset_template_sizer  = nullptr;
    wxPanel *                                          m_filament_preset_panel          = nullptr;
    wxPanel *                                          m_process_preset_panel           = nullptr;
    wxPanel *                                          m_preset_template_panel          = nullptr;
    std::string                                        m_custom_texture;
    std::string                                        m_custom_model;
};

enum SuccessType {
    PRINTER = 0,
    FILAMENT
};

class CreatePresetSuccessfulDialog : public DPIDialog
{
public:
    CreatePresetSuccessfulDialog(wxWindow *parent, const SuccessType &create_success_type);
    ~CreatePresetSuccessfulDialog();

protected:
    void on_dpi_changed(const wxRect &suggested_rect) override;

private:
    Button *m_button_ok     = nullptr;
    Button *m_button_cancel = nullptr;
};

class ExportConfigsDialog : public DPIDialog
{
public:
    ExportConfigsDialog(wxWindow *parent);
    ~ExportConfigsDialog();//to do: delete preset

protected:
    void        on_dpi_changed(const wxRect &suggested_rect) override;
    wxBoxSizer *create_txport_config_item(wxWindow* parent);
    wxBoxSizer *create_button_item(wxWindow *parent);
    wxBoxSizer *create_select_printer(wxWindow *parent);

    wxBoxSizer *create_radio_item(wxString title, wxWindow *parent, wxString tooltip, std::vector<std::pair<RadioBox *, wxString>> &radiobox_list);

    struct ExportType
    {
        wxString preset_bundle;
        wxString printer_preset;
        wxString filament_preset;
        wxString process_preset;
    };

    enum ExportCase {
        INITIALIZE_FAIL = 0,
        ADD_FILE_FAIL,
        FINALIZE_FAIL,
        OPEN_ZIP_WRITTEN_FILE,
        EXPORT_SUCCESS,
    };

private:
    void data_init();
    void select_curr_radiobox(std::vector<std::pair<RadioBox *, wxString>> &radiobox_list, int btn_idx);
    ExportCase archive_preset_bundle_to_file(const wxString &path);
    ExportCase archive_printer_preset_to_file(const wxString &path);
    ExportCase archive_filament_preset_to_file(const wxString &path);
    ExportCase archive_process_preset_to_file(const wxString &path);

private:
    std::vector<std::pair<RadioBox *, wxString>>           m_export_type_btns;
    std::vector<std::pair<CheckBox *, Preset *>>           m_preset;
    std::unordered_map<std::string, Preset *>              m_printer_presets;
    std::unordered_map<std::string, std::vector<Preset *>> m_filament_presets;
    std::unordered_map<std::string, std::vector<Preset *>> m_process_presets;
    ExportType                                             m_exprot_type;
    wxGridSizer *                                          m_preset_sizer   = nullptr;
    wxWindow *                                             m_presets_window = nullptr;
    Button *                                               m_button_ok      = nullptr;
    Button *                                               m_button_cancel  = nullptr;
};

}
}
#endif