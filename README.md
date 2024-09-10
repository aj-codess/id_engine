Beryl is an id generating engine made solely made for giving identity to clients on the server.

identity includes relevant information which governs tracking clients and their relative data

paths:
"/beryl/id" - params-> options , user_id , space-id
"/beryl/persistent_data"
"/beryl/del_user_id" - params -> user_id , user_pos
"/beryl/del_space_id" - params -> space_id , space_pos
"beryl/del_ugc" - params -> user_id , ugc_id

when making a request, query parameters should be based on the above chosen names

---Task associated with id_schema.h----

std::string user_id=schema.generate_id("0","0","0");

std::string space_id=schema.generate_id("2","0","0");

cout<<"user - "<<schema.generate_id("0","0","0")<<endl;
cout<<"ugc - "<<schema.generate_id("1",user_id,"0")<<endl;
cout<<"space - "<<schema.generate_id("2","0","0")<<endl;
cout<<"space ugc - "<<schema.generate_id("3",user_id,space_id)<<endl;
cout<<"chat - "<<schema.generate_id("4",user_id,"0")<<endl;
cout<<"space chat - "<<schema.generate_id("5",user_id,space_id)<<endl;





generate id
takes 3 args->

option -> 0-user 
	->1-ugc
	->2-space
	->3-space_ugc
	->4-chat
	->5-space_c
	
user_id_f_ugc - string of user id

space_id_f_ugc - string of space id for ugc


for user 
(0,0,0)


for ugcID
(1,userID,0)


for spaceID
(2,0,0)


for space ugc
(3,userID,spaceID)



for chat
(4,userID,0)



for space chat
(5,userID,spaceID)




//things to query schema server aside id
current_time_id_len
current_user_num
current_space_num

