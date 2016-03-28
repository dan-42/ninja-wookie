

#include <bacnet/bvll/common/bacnet_ip_address.hpp>
#include <bacnet/bvll/detail/bacnet_ip_address_grammar.hpp>

namespace bacnet { namespace bvll { namespace generator {

  bool generate(bacnet::binary_data c, bacnet_ip_address &v) {
    std::back_insert_iterator<std::decay<decltype(c)>::type> sink(c);
    bacnet::bvll::detail::generator::bacnet_ip_address_grammar<decltype(sink)> g;
    return boost::spirit::karma::generate(sink, g, v);
  }

}}}


namespace bacnet { namespace bvll { namespace parser {

  bool parse(bacnet::binary_data &i, bacnet_ip_address &v){
    auto start = i.begin(); auto end = i.end();
    bacnet::bvll::detail::parser::bacnet_ip_address_grammar<decltype(start)> grammar;
    return boost::spirit::qi::parse(start, end, grammar, v);
  }


}}}