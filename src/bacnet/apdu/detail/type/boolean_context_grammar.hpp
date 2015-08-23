//
// Created by dan on 8/23/15.
//

#ifndef NINJA_WOOKIE_BOOLEAN_CONTEXT_GRAMMAR_HPP
#define NINJA_WOOKIE_BOOLEAN_CONTEXT_GRAMMAR_HPP


#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>



namespace bacnet { namespace  apdu { namespace detail { namespace type { namespace parser {

          using namespace boost::spirit;
          using namespace boost::spirit::qi;
          using namespace boost::phoenix;

          using boost::spirit::qi::bit_field;
          using boost::spirit::qi::rule;
          using boost::spirit::qi::_1;
          using boost::phoenix::bind;


          template<typename Iterator>
          struct boolean_context_grammar : grammar<Iterator, bool()> {


            rule<Iterator, bool()>     bool_rule;

            rule<Iterator, bool()>     context_tagged_rule;
            rule<Iterator, bool()>     context_tagged_true_rule;
            rule<Iterator, bool()>     context_tagged_false_rule;

            boolean_context_grammar() : boolean_context_grammar::base_type(bool_rule){

              constexpr uint8_t encoded_context_tag_id       = 0x29;
              constexpr uint8_t encoded_context_tagged_true  = 0x01;
              constexpr uint8_t encoded_context_tagged_false = 0x00;

              bool_rule  = context_tagged_rule;


              context_tagged_rule = byte_(encoded_context_tag_id) >> (context_tagged_true_rule|context_tagged_false_rule);

              context_tagged_true_rule = byte_(encoded_context_tagged_true)[_val = true];
              context_tagged_false_rule = byte_(encoded_context_tagged_false)[_val = false];
            }
          };

}}}}}




#endif //NINJA_WOOKIE_BOOLEAN_CONTEXT_GRAMMAR_HPP
