#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Animal {
public:
  Animal() = default;
  Animal(std::string Name, int Legs) : Name(Name), Legs(Legs) {}
  int legs() const {return Legs;}
  std::string name() {return Name;}
private:
  friend class boost::serialization::access;
  template <typename Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & Name;
    ar & Legs;
  }
  int Legs;
  std::string Name;
};
