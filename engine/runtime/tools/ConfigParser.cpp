#include "../../runtime/tools/ConfigParser.hpp"
#include "../../runtime/tools/RegexHelper.hpp"

namespace ExCCCRender::Tools {
void ConfigParser::Parser() {
    std::optional<std::string> line{};
    bool                       flag_config_name  = false;
    bool                       flag_config_key   = false;
    bool                       flag_config_value = false;
    // If one of them(flag_config_name,flag_config_key,flag_config_value) is not completed, continue until all are
    // completed
    do {
        line            = ReadNextLine();
        std::string str = *line;
        if (str == "")
            continue;

        clear_space(str);
        // annotation, 注释
        auto pos = str.find_first_of(';');
        if (pos != std::string::npos) {
            str = str.substr(0, pos);
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
        if (std::regex_match(str, match, config_name)) {
            // go into the config item
            item.config_name = match[1];
            flag_config_name = true;
        } else if (std::regex_match(str, match, config_item)) {
            item.key                      = match[1];
            flag_config_key               = true;
            std::string config_item_value = match[2];
            item.value                    = *(parser_config_value(config_item_value));
            flag_config_value             = true;
        } else {
            std::cerr << "error string is : {" << str << "}" << std::endl;
            throw std::invalid_argument("Invalid config");
        }
        if (flag_config_name && flag_config_key && flag_config_value) {
            this->ConfigInfo.push_back(item);
            flag_config_name  = false;
            flag_config_key   = false;
            flag_config_value = false;
            item              = {};
        }
    } while (line != std::nullopt);
}

std::optional<detail::_Value_Type> ConfigParser::parser_config_value(const std::string& config_item_value) {
    std::string value = config_item_value;
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);
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
        return value.substr(1, value.size() - 2);
    }

    // variable check
    const std::regex variable_pattern(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
    if (std::regex_match(value, variable_pattern))
        return value;

    throw std::invalid_argument("Invalid config item value: " + config_item_value);
    return std::nullopt;
}

void ConfigParser::PrintConfigInfo() const {
    for (const auto& item : ConfigInfo) {
        std::cout << std::format("Config: {}, Key:{}, Value: ", item.config_name, item.key);
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
}  // namespace ExCCCRender::Tools