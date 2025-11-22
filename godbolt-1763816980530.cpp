    ::add_convention<MemArea, double() noexcept>
    ::support_copy<pro::constraint_level::nontrivial>
    ::build {};

class Rectangle {
 public:
  Rectangle(double width, double height) : width_(width), height_(height) {}
  Rectangle(const Rectangle&) = default;

  void Draw(std::ostream& out) const {
    out << "{Rectangle: width = " << width_ << ", height = " << height_ << "}";
  }
  double Area() const noexcept { return width_ * height_; }

 private:
  double width_;
  double height_;
};

std::string PrintDrawableToString(pro::proxy<Drawable> p) {
  std::stringstream result;
  result << "entity = ";
  p->Draw(result);
  result << ", area = " << p->Area();
  return std::move(result).str();
}

int main() {
  pro::proxy<Drawable> p = pro::make_proxy<Drawable, Rectangle>(3, 5);
  std::string str = PrintDrawableToString(p);
  std::cout << str << "\n";  // Prints "entity = {Rectangle: width = 3, height = 5}, area = 15"
}

struct Drawable : pro::facade_builder
    ::add_convention<MemDraw, void(std::ostream& output)>
PRO_DEF_MEM_DISPATCH(MemDraw, Draw);
PRO_DEF_MEM_DISPATCH(MemArea, Area);

#include <iostream>
#include <sstream>

#include <proxy/proxy.h>


// Link: https://godbolt.org/z/E95nY7PYq