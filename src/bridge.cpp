#include "bridge.hpp"

using namespace v8;

int age = 41;

// --------------------------------------------------

void print(void)
{
    std::cout << "print" << std::endl;
}

void doit(const FunctionCallbackInfo<Value> &args)
{
    String::Utf8Value str(args.GetIsolate(), args[0]);
    printf("doit argument = %s...\n", *str);
    args.GetReturnValue().Set(String::NewFromUtf8(args.GetIsolate(), "doit...done", NewStringType::kNormal).ToLocalChecked());
}

void age_getter(Local<String> property, const PropertyCallbackInfo<Value> &info)
{
    printf("age_getter...\n");
    info.GetReturnValue().Set(age);
}

void age_setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void> &info)
{
    printf("age_setter...\n");
    age = value->Int32Value(info.GetIsolate()->GetCurrentContext()).FromJust();
}

void property_listener(Local<String> name, const PropertyCallbackInfo<Value> &info)
{
    String::Utf8Value utf8_value(info.GetIsolate(), name);
    std::string key = std::string(*utf8_value);
    printf("ageListener called for nam %s.\n", key.c_str());
}

// --------------------------------------------------

void print(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    String::Utf8Value str(args.GetIsolate(), args[0]);
    printf("%s", *str);
    // args.GetReturnValue().Set(String::NewFromUtf8(args.GetIsolate(), "doit...done", NewStringType::kNormal).ToLocalChecked());
}

// --------------------------------------------------

sf::RenderWindow window;

void sfml_create_window(const FunctionCallbackInfo<Value> &args)
{
    // std::cout << "One" << std::endl;
    window.create(sf::VideoMode(800, 600), "My window");
    window.setVerticalSyncEnabled(true);
    // std::cout << "Two" << std::endl;
}

void sfml_is_window_open(const FunctionCallbackInfo<Value> &args)
{
    std::cout << "sfml_is_window_open\n" << std::endl;
    args.GetReturnValue().Set(v8::Boolean::New(args.GetIsolate(), window.isOpen()));
}

// --------------------------------------------------

sf::Event event;

void sfml_poll_event(const FunctionCallbackInfo<Value> &args)
{
    std::cout << "sfml_poll_event\n" << std::endl;
    args.GetReturnValue().Set(v8::Boolean::New(args.GetIsolate(), window.pollEvent(event)));
}

void sflm_handle_window_close_event(const FunctionCallbackInfo<Value> &args)
{
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }
}

// --------------------------------------------------

void sfml_window_clear(const FunctionCallbackInfo<Value> &args)
{
    window.clear(sf::Color::Black);
}

void sfml_window_display(const FunctionCallbackInfo<Value> &args)
{
    window.display();
}

// --------------------------------------------------

// void sfml_window_set_position(int x, int y){
//     window.setPosition(sf::Vector2i(x, y));
// }

// void sfml_window_set_size(int w, int h){
//     window.setSize(sf::Vector2u(w, h));
// }

// void sfml_window_set_title(const char *title){
//     window.setTitle(title);
// }

// --------------------------------------------------

void test()
{
    std::cout << "test" << std::endl;
}
