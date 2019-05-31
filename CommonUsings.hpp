#pragma once

template <typename HolderType,
          typename IdType>
using AllocationBehaviour = std::unique_ptr<IAllocationStrategy<HolderType, IdType>>;
