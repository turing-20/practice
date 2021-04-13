
flag = 0


def Make_Linked_List(Head, root):

    if(root.left != NULL):
        Head = Make_linked_list(Head, root.left)

    if(root.right != NULL):
        Head = Make_Linked_List(Head, root.right)

    if(root.left == NULL):
        flag = 1
        return

    if(root.right == NULL and root.left == NULL):
        Head.next = root
        Head.next.prev = Head
        return Head.next

    a


b      c

head = b

head -> prev = Null
head -> next = c


def main(root):
    Head = Node()

    temp = root

    while(temp.left != NULL):
        temp = temp.left

    Head = temp
    Head.prev = NULL
    Make_Linked_List(Head, root)
