/**
 * @file graph/hnode_collection_iterator.h 
 * @brief delcaration of hnode_collection_iterator class.
 */

class hnode;
#include <vector>

typedef std::vector<hnode*> hnode_collection;

/**
 * @class hnode_collection_iterator
 * @brief Iterator on hnode collection.
 */
class hnode_collection_iterator
{
public:
    /**
     * @brief Resets iterator.
     */
    void reset();

public:
    /**
     * @brief Gets next node.
     * @note if iteration reached end, returns nullptr.
     */
    hnode* next();

public:
    /**
     * @brief Constructor.
     * @param c Collection to iterate.
     */
    hnode_collection_iterator(const hnode_collection& c);

private:
    const hnode_collection& m_collection;
    unsigned m_index;
};

