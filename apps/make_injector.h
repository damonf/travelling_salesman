#ifndef __MAKE_INJECTOR_H
#define __MAKE_INJECTOR_H

#include "genetic.h"
#include "random_generator.h"
#include "natural_selector.h"
#include "parent_selector.h"
#include "breeder.h"
#include "mutator.h"
#include "random_numbers.h"
#include "irandom_numbers.h"

#include <boost/di.hpp>

namespace di = boost::di;

inline auto make_injector() {

    constexpr size_t genetic_alg_pop_size = 100;

    return di::make_injector(
              di::bind<tsp::IRandomGenerator>().to<tsp::RandomGenerator>()
            , di::bind<tsp::INaturalSelector>().to<tsp::NaturalSelector>()
            , di::bind<>.to(tsp::PopSize{genetic_alg_pop_size})
            , di::bind<tsp::IRandomNumbers<size_t>>().to<tsp::RandomNumbers<size_t>>()
            , di::bind<tsp::IRandomNumbers<double>>().to<tsp::RandomNumbers<double>>()
            , di::bind<tsp::IParentSelector>().to<tsp::ParentSelector>()
            , di::bind<tsp::IBreeder>().to<tsp::Breeder>()
            , di::bind<tsp::IMutator>().to<tsp::Mutator>()
            );
}

#endif // __MAKE_INJECTOR_H
