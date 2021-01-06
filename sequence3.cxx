//FILE: sequence3.cxx
//CLASS implemented : sequence(See sequence3.h for documentation.)
//INVARIANT for the sequence class :
//1. The items in the sequence are stored in a linked list.
//2. The head pointer of the list is stored in the member variable head_pointer.
//3. The total number of items in the list is stored in the member variable many_nodes.
//4. The tail_pointer member variable points to the tail node of the list.
//5. The cursor points to the node containg the current item. It is used for attaching nodes.
//6. The precursor points the node before the current node. It is used for inserting nodes.
#include "sequence3.h"
#include <cassert>


namespace main_savitch_5
{
	//Big-O: Linked-List O(n), Dynamic Array O(n)
	sequence::sequence(const sequence& source)
	{
		if (this == &source)
			return;

		else if (source.cursor == NULL)
		{
			list_copy(source.head_pointer, head_pointer, tail_pointer);
			many_nodes = source.size();
			cursor = NULL;
			precursor = NULL;
		}

		else if (source.cursor == source.head_pointer)
		{
			list_copy(source.head_pointer, head_pointer, tail_pointer);
			many_nodes = source.size();
			precursor = NULL;
			cursor = head_pointer;
		}

		else
		{
			if (source.head_pointer == NULL)
				return;

			node *temp;
			list_head_insert(head_pointer, source.head_pointer->data());
			precursor = head_pointer;
			temp = source.head_pointer->link();
			while (temp != source.cursor)
			{
				list_insert(precursor, temp->data());
				precursor = precursor->link();
				temp = temp->link();
			}
			list_copy(source.cursor, cursor, tail_pointer);
			precursor->set_link(cursor);
			many_nodes = source.size();
			
		}
	}

	//Big-O: Linked-List O(n), Dynamic Array O(n)
	sequence::~sequence()
	{
		list_clear(head_pointer);
		many_nodes = 0;
		
		
		
	}

	// MODIFICATION MEMBER FUNCTIONS
	//Big-O: Linked-List O(1), Dynamic Array O(1)
	void sequence::start()
	{
		if (many_nodes > 0)
		{
			cursor = head_pointer;
			precursor = NULL;
		}
	}

	//Big-O: Linked-List O(1) Dynamic Array O(1)
	void sequence::advance()
	{
		assert(is_item());

		if (cursor->link() == NULL)
		{
			cursor = NULL;
			precursor = NULL;
		}

		else
		{
			precursor = cursor;
			cursor = cursor->link();
			
		}
	}

	//Big-O: Linked-List  O(1), Dynamic Array O(n) (Middle) O(1)(Beginning/End)
	void sequence::insert(const value_type& entry)
	{
		if (size() == 0)
		{
			head_pointer = new node(entry);
			cursor = head_pointer;
			tail_pointer = cursor;
			many_nodes++;
		}

		else if (size() > 1 && cursor != NULL)
		{
			if (precursor == NULL)
			{
				list_head_insert(head_pointer, entry);
				head_pointer->set_link(cursor);
				cursor = head_pointer;
				precursor = NULL;
				many_nodes++;
			}
			else
			{
				list_insert(precursor, entry);
				cursor = precursor->link();
				many_nodes++;
			}
		}
		
		else if (size() > 1 && cursor == NULL)
		{
			head_pointer = new node(entry, head_pointer);
			cursor = head_pointer;
			many_nodes++;
		}
		
		else if (size() == 1)
		{
			
			list_head_insert(head_pointer, entry); 
			head_pointer->set_link(tail_pointer);
			cursor = head_pointer;
			
			many_nodes++;
		}

	}

	//Big-O: Linked-List  O(1), Dynamic Array O(n)(Middle) O(1)(Beginning/End)
	void sequence::attach(const value_type& entry)
	{
		 if (size() == 0)
		 {
			 head_pointer = new node(entry);
			 cursor = head_pointer;
			 tail_pointer = cursor;
			 many_nodes++;
		 }

		 else if (size() > 1 && cursor == NULL)
		 {
			 precursor = tail_pointer;
			 node *new_pointer = new node(entry);
			 tail_pointer->set_link(new_pointer);
			 tail_pointer = new_pointer;
			 cursor = tail_pointer;
			
			 many_nodes++;
		 }

		 else if (size() > 1 && cursor != NULL)
		 {
			 precursor = cursor;
			
			 node *new_pointer = new node(entry);
			 new_pointer->set_link(cursor->link());
			 if(new_pointer->link() == NULL)
				 tail_pointer = new_pointer;
			 cursor->set_link(new_pointer);
			 cursor = new_pointer;
			 
			 many_nodes++;
		 }

		 else if (size() == 1 && cursor != NULL)
		 {
			 list_insert(cursor, entry);
			 precursor = head_pointer;
			 cursor = precursor->link();
			 tail_pointer = cursor;
			 many_nodes++;
		 }

		 else if (size() == 1 && cursor == NULL)
		 {
			 node *new_pointer = new node(entry);
			 tail_pointer->set_link(new_pointer);
			 tail_pointer = new_pointer;
			 precursor = head_pointer;
			 cursor = tail_pointer;
			 
			 many_nodes++;
		 }
	}

	//Big-O: Linked-List  O(1), Dynamic Array O(n)(Middle) O(1)(Beginning/End)
	void sequence::remove_current()
	{
		assert(is_item());
		if (precursor != NULL)
		{
			if (cursor != tail_pointer)
			{
				list_remove(precursor);
				cursor = precursor->link();
				
			}

			else
			{
				tail_pointer = precursor;
				list_remove(precursor);
				precursor = NULL;
				cursor = NULL;
			}

		}
		else
		{
			list_head_remove(head_pointer);
			cursor = head_pointer;
			if(size() == 1)
				tail_pointer = head_pointer;
		}
		many_nodes--;
	}

	//Big-O: Linked-List O(n), Dynamic Array O(n)
	void sequence::operator =(const sequence& source)
	{
		if (this == &source)
			return;
		
		if (source.cursor == NULL)
		{
			list_clear(head_pointer);
			many_nodes = 0;
			list_copy(source.head_pointer, head_pointer, tail_pointer);
			many_nodes = source.many_nodes;
			precursor = NULL;
			cursor = NULL;
		}

		else if (source.precursor == NULL)
		{
			list_clear(head_pointer);
			many_nodes = 0;
			list_copy(source.head_pointer, head_pointer, tail_pointer);
			many_nodes = source.many_nodes;
			cursor = head_pointer;
			precursor = NULL;
		}

		else if (source.precursor != NULL)
		{
			list_clear(head_pointer);
			node *temp;
			list_head_insert(head_pointer, source.head_pointer->data());
			precursor = head_pointer;
			temp = source.head_pointer->link();
			while (temp != source.cursor)
			{
				list_insert(precursor, temp->data());
				precursor = precursor->link();
				temp = temp->link();
			}
			list_copy(source.cursor, cursor, tail_pointer);
			precursor->set_link(cursor);
			many_nodes = source.size();
		}
		
	}

	// CONSTANT MEMBER FUNCTIONS
	//Big-O: Linked-List O(1), Dynamic Array O(1)
	bool sequence::is_item() const
	{
		if(cursor != NULL)
			return 1;
		else
			return 0;
	}

	//Big-O: Linked-List O(1), Dynamic Array O(1)
	sequence::value_type sequence::current() const
	{
		assert(is_item());
		if(cursor != NULL)
			return cursor->data();

	}

}