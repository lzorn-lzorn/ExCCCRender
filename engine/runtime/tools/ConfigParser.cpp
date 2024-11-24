#include "../../runtime/tools/ConfigParser.hpp"
#include "../../runtime/tools/RegexHelper.hpp"
#include "../../runtime/tools/debug.hpp"

namespace ExCCCRender::Tools {
void ConfigParser::Parser() {
    std::vector<std::string> lines = GetFileContents();

    if (lines.empty()) {
        return;
    }
    bool flag_config_name  = false;
    bool flag_config_key   = false;
    bool flag_config_value = false;

    std::string          line;
    size_t               size = lines.size();
    detail::_Config_Type config{};
    // If one of them(flag_config_name,flag_config_key,flag_config_value) is not completed, continue until all are
    // completed
    for (size_t i = 0; i < size; i++) {

        line = lines[i];
        // space, 空格
        clear_space(line);
        // annotation, 注释
        clear_annotation(line);

        if (line.empty()) {
            continue;
        }
        // [VariableName]
        auto RH_Instance       = RegexPattern::RegexHelper::GetInstance();
        auto variable_pattern  = RH_Instance.Get()["variable"];
        auto float_pattern     = RH_Instance.Get()["float"];
        auto string_pattern    = RH_Instance.Get()["string"];
        auto integer_pattern   = RH_Instance.Get()["integer"];
        auto boolean_pattern   = RH_Instance.Get()["boolean"];
        auto character_pattern = RH_Instance.Get()["character"];

        auto key_pattern   = variable_pattern;
        auto value_pattern = RH_Instance.regex_or(
            variable_pattern, float_pattern, string_pattern, integer_pattern, boolean_pattern, character_pattern);

        auto config_name_pattern = RH_Instance.bracket_of_('[', variable_pattern);
        auto congig_item_pattern = RH_Instance.equation(key_pattern, value_pattern);

        std::regex config_name(config_name_pattern);
        std::regex config_item(congig_item_pattern);

        std::smatch     match;
        detail::IniItem item{};

        if (std::regex_match(line, match, config_name)) {
            // go into the config item
            config = match[1];
        } else if (std::regex_match(line, match, config_item)) {
            item.config_name              = config;
            item.key                      = match[1];
            std::string config_item_value = match[2];
            item.value                    = *(parser_config_value(config_item_value));
        } else {
            std::cerr << "error string is : {" << line << "}" << std::endl;
            throw std::invalid_argument("Invalid config");
        }
        this->ConfigInfo.push_back(item);
        item = {};
    }
}

std::optional<detail::_Value_Type> ConfigParser::parser_config_value(const std::string& config_item_value) {
    std::string value = config_item_value;
    // boolean
    if (value == "ture")
        return true;
    if (value == "false")
        return false;
    // int
    const std::regex int_pattern(R"(^-?\d+$)");
    if (std::regex_match(value, int_pattern))
        return std::stoi(value);

    // float, double
    const std::regex float_pattern(R"(^-?\d+(\.\d+)?$)");
    if (std::regex_match(value, float_pattern)) {
        try {
            float float_value = std::stof(value);
            return float_value;
        } catch (const std::out_of_range&) {
            double double_value = std::stod(value);
            return double_value;
        }
    }

    // std::string
    if ((value.front() == '"' && value.back() == '"') || (value.front() == '\'' && value.back() == '\'')) {
        return value;
    }

    // variable check
    const std::regex variable_pattern(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
    if (std::regex_match(value, variable_pattern))
        return value;

    throw std::invalid_argument("Invalid config item value: " + config_item_value);
    return std::nullopt;
}

void ConfigParser::PrintConfigInfo() const {
    if (ConfigInfo.empty()) {
        std::cout << "Config is empty" << std::endl;
    }
    for (const auto& item : ConfigInfo) {
        std::cout << std::format(" Config-{}, Key:{}, Value: ", item.config_name, item.key);
        print_config_value(item.value);
        std::cout << std::endl;
    }
}

void ConfigParser::clear_space(std::string& str) const {
    str.erase(std::remove_if(str.begin(),
                             str.end(),
                             [](unsigned char c) {
                                 return std::isspace(c);
                             }),
              str.end());
}

void ConfigParser::clear_annotation(std::string& str) const {
    auto pos = str.find_first_of(';');
    if (pos != std::string::npos) {
        str = str.substr(0, pos);
    }
}
}  // namespace ExCCCRender::Tools