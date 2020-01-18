#include "IndexTree.h"

IndexNode::IndexNode(const IndexNode& other)
	: m_index(other.m_index)
{
	if (other.m_next != nullptr) m_next = std::make_unique<IndexNode>(*other.m_next);
}

IndexNode& IndexNode::operator=(const IndexNode& other)
{
	if (&other == this)
	{
		return *this;
	}

	m_index = other.m_index;
	if (other.m_next != nullptr)
	{
		m_next = std::make_unique<IndexNode>(*other.m_next);
	}
	else
	{
		m_next = nullptr;
	}

	return *this;
}
