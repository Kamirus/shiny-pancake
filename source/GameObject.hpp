#include <v8.h>
#include <string>
#pragma once

struct GameObject{
	int x;
	int y;
	unsigned team;
	std::string type;
	unsigned id;
	GameObject(std::string type_, unsigned team_, int x_, int y_) :
		x (x_), y{y_}, type{type_}, team{team_}, id{0}
	{}
	v8::Local<v8::Object> getData(v8::Isolate* isolate)
	{
		v8::Local<v8::Object> object = v8::Object::New(isolate);
		getValue(isolate, object);
		return object;
	}
	virtual void update(float dt){};
	virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object){
	  object->Set(v8::String::NewFromUtf8(isolate, "_id_"),
	              v8::Number::New(isolate, id));
	  object->Set(v8::String::NewFromUtf8(isolate, "posx"),
	              v8::Number::New(isolate, x));
	  object->Set(v8::String::NewFromUtf8(isolate, "posy"),
	              v8::Number::New(isolate, y));
	  object->Set(v8::String::NewFromUtf8(isolate, "team"),
	              v8::Number::New(isolate, team));
	  object->Set(v8::String::NewFromUtf8(isolate, "type"),
	               v8::String::NewFromUtf8(isolate, type.c_str()));
	}
};

struct Ball : public GameObject
{
	Ball() : GameObject{"Basic", 0, 0, 0} {}
	virtual void update(float dt){ x++; y++; };
	virtual void getValue(v8::Isolate* isolate, v8::Local<v8::Object> object) {
		GameObject::getValue(isolate, object);
		object->Set(v8::String::NewFromUtf8(isolate, "XD"),
	               v8::String::NewFromUtf8(isolate, "XD"));
	}
};