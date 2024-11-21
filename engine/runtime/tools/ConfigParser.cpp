#include "../../runtime/tools/ConfigParser.hpp"

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
        str.erase(0, str.find_first_not_of(" \t"));
        str.erase(str.find_last_not_of(" \t") + 1);
        // annotation
        auto pos = str.find_first_of(';');
        if (pos != std::string::npos) {
            str = str.substr(0, pos);
        }
        if (str == "")
            continue;

        std::regex config_name_pattern(R"(^\[([a-zA-Z_][a-zA-Z0-9_ ]*)\]$)");
        std::regex congig_item_pattern(
            R"(^\s*([a-zA-Z_][a-zA-Z0-9_]*(?:\s+[a-zA-Z_][a-zA-Z0-9_]*)*)\s*=\s*(?:(?:[a-zA-Z_][a-zA-Z0-9_]*(?:\s+[a-zA-Z_][a-zA-Z0-9_]*)*)|(?:-?\d+)|(?:-?\d+\.\d+)|(?:true|false)|(?:'[^']')|(?:\"[^\"]*\"))\s*$
)");

        std::smatch     match;
        detail::IniItem item{};
        if (std::regex_match(str, match, config_name_pattern)) {
            // go into the config item
            item.config_name = match[1];
            flag_config_name = true;
        } else if (std::regex_match(str, match, congig_item_pattern)) {
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
}  // namespace ExCCCRender::Tools