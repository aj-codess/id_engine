Beryl is an id generating engine made solely made for giving identity to clients on the server.

identity includes relevant information which governs tracking clients and their relative data

paths:
/beryl/id
/beryl/del_user_id
/beryl/del_space_id


---Task associated with id_schema.h----

std::string user_id=schema.generate_id("0","0","0");

std::string space_id=schema.generate_id("2","0","0");

cout<<"user - "<<schema.generate_id("0","0","0")<<endl;
cout<<"ugc - "<<schema.generate_id("1",user_id,"0")<<endl;
cout<<"space - "<<schema.generate_id("2","0","0")<<endl;
cout<<"space ugc - "<<schema.generate_id("3",user_id,space_id)<<endl;
cout<<"chat - "<<schema.generate_id("4",user_id,"0")<<endl;
cout<<"space chat - "<<schema.generate_id("5",user_id,space_id)<<endl;
