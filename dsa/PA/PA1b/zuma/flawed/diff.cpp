89,91c89,93
< 	while (count + p->size() < r + 1 && p != END)
< 	{
< 		count += p->size();
---
> 	while (count <= r && p != END) {
> 		if (r < count + p->size()) {
> 			break;
> 		}
> 		count = count + p->size();
195a198
> 		who->balls.insert(cur_rank, value);
200,204d202
< 		//判断是否会是连锁反应的开端
< 		if (count < 2)
< 		{
< 			who->balls.insert(cur_rank, value);
< 		}
206,232c204,216
< 		else
< 		{
< 			int count1 = 0;	Node* start = lParent, * end = rParent;	char left = char(1), right = char(2);
< 			if (lParent->size() != 0)
< 				left = lParent->balls[head];
< 			if (rParent->size() != 0)
< 				right = rParent->balls[tail];
< 			//寻找相消的开头、结束节点
< 			while (left == right)
< 			{
< 				lParent = start;	rParent = end;	count1 = 0;
< 				int iniHead = head, iniTail = tail;
< 				checkLeft(lParent, start, head, count1, left);
< 				checkRight(rParent, end, tail, count1, right);
< 				if (count1 < 3)	//连环结束,将头尾指针放回
< 				{
< 					head = iniHead;	tail = iniTail;
< 					start = lParent;	end = rParent;
< 					break;
< 				}
< 				if (start->size() != 0)
< 					left = start->balls[head];
< 				if (end->size() != 0)
< 					right = end->balls[tail];
< 			}
< 			//找到 [head,tail)，即将head向右挪动一格
< 			while (head + 1 >= start->size())		//确保head不会走到 END:前提已经满足必定有相消位
---
> 		if (count <= 2) continue;
> 
> 		Node* start = lParent, * end = rParent;
> 		char left = lParent->balls[head];
> 		char right = rParent->balls[tail];
> 		//寻找相消的开头、结束节点
> 		while (left == right)
> 		{
> 			lParent = start;	rParent = end;	count = 0;
> 			int iniHead = head, iniTail = tail;
> 			checkLeft(lParent, start, head, count, left);
> 			checkRight(rParent, end, tail, count, right);
> 			if (count < 3)	//连环结束,将头尾指针放回
234,235c218,220
< 				start = start->next;
< 				head = -1;
---
> 				head = iniHead;	tail = iniTail;
> 				start = lParent;	end = rParent;
> 				break;
237c222,224
< 			head++;
---
> 			left = start->balls[head];
> 			right = end->balls[tail];
> 		}
239,247c226,241
< 			if (start == end)					//位于同一节点，直接移除
< 				start->balls.remove(head, tail);
< 			else
< 			{									//位于不同节点，将中间节点从链表中移除
< 				start->balls.remove(head, start->size());
< 				end->balls.remove(0, tail);
< 				start->next = end;
< 				end->prev = start;
< 			}
---
> 		//找到 [head,tail)，即将head向右挪动一格
> 		head = head + 1;
> 		while (head >= start->size())		//确保head不会走到 END:前提已经满足必定有相消位
> 		{
> 			start = start->next;
> 			head = 0;
> 		}
> 
> 		if (start == end)					//位于同一节点，直接移除
> 			start->balls.remove(head, tail);
> 		else
> 		{									//位于不同节点，将中间节点从链表中移除
> 			start->balls.remove(head, start->size());
> 			end->balls.remove(0, tail);
> 			start->next = end;
> 			end->prev = start;
