#include "arnio/column.h"
#include <stdexcept>

namespace arnio {

Column::Column(const std::string& name, DType dtype)
    : name_(name), dtype_(dtype) {}

Column::Column(const std::string& name, DType dtype, std::vector<CellValue> data, std::vector<bool> null_mask)
    : name_(name), dtype_(dtype), data_(std::move(data)), null_mask_(std::move(null_mask)) {}

const std::string& Column::name() const { return name_; }
DType Column::dtype() const { return dtype_; }
size_t Column::size() const { return data_.size(); }

bool Column::is_null(size_t idx) const {
    if (idx >= null_mask_.size()) {
        throw std::out_of_range("Column index out of range");
    }
    return null_mask_[idx];
}

const CellValue& Column::at(size_t idx) const {
    if (idx >= data_.size()) {
        throw std::out_of_range("Column index out of range");
    }
    return data_[idx];
}

size_t Column::memory_usage() const {
    size_t usage = sizeof(Column);
    usage += name_.capacity();
    usage += data_.capacity() * sizeof(CellValue);
    usage += null_mask_.capacity() * sizeof(bool);
    // Approximate string storage within variants
    for (const auto& cell : data_) {
        if (std::holds_alternative<std::string>(cell)) {
            usage += std::get<std::string>(cell).capacity();
        }
    }
    return usage;
}

void Column::push_back(const CellValue& value) {
    data_.push_back(value);
    null_mask_.push_back(std::holds_alternative<std::monostate>(value));
}

void Column::push_null() {
    data_.push_back(std::monostate{});
    null_mask_.push_back(true);
}

void Column::set_name(const std::string& name) { name_ = name; }
void Column::set_dtype(DType dtype) { dtype_ = dtype; }

const std::vector<CellValue>& Column::data() const { return data_; }
const std::vector<bool>& Column::null_mask() const { return null_mask_; }

Column Column::clone() const {
    return Column(name_, dtype_, data_, null_mask_);
}

} // namespace arnio
