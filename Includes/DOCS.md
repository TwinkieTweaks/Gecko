# Gecko
`namespace Gecko` is an Angelscript-based scripting engine for usage alongside Trackmania titles. 
This file serves as documentation as to how to properly format C++ stuff that binds to Angelscript.

## Namespaces
When porting functions from Openplanet, keep in mind to also keep the namespace structure identical (with minor differences) between Angelscript and C++.
An example are the `yield()` and `yield(uint)` functions. Since they are globals, our C++ implementations are in `namespace Gecko::Exports::Global`.

## Functions
Next up, when naming the C++ functions, keep in mind that Angelscript does not support binding overloaded functions, so you can't just make `void yield()` and `void yield(uint32_t frames)` in C++ and call it a day.
So when making functions to be bound, keep their names in C++ as close to what they are bound to in Angelscript (including naming style and capitalization).
In this example, they are named `void yield()` and `void yieldFor(uint32_t frames)` respectively.

## Registering
After you're done making the C++ implementations of your Angelscript functions, you need to make a registrar.
A `void Gecko::Exports::*::Registrar(asIScriptEngine*)` is a function that registers all exports of a single namespace to an Angelscript engine.
After you make your registrar, call it in `Gecko::ScriptManager::ScriptManager()` (`ScriptManager` ctor) with the `&ScriptManager.Engine`.
You can also optionally create a `void Gecko::Exports::*::Cleanup()` function and add it to the `ScriptManager`'s dtor.

## Callbacks
Callbacks' implementations depend on 3 things:
- `struct Gecko::CtxSet`'s script contexts for each callback
- `const char* Gecko::CallbackTypeSignatures[]`' callback type implementations
- `enum class Gecko::CallbackType` enum for the callback

Indicies of callbacks don't matter (except for `Gecko::CallbackType::Main` which must always be zero), all that is needed is that when the callbacks are named in `CallbackTypeSignatures` and `CallbackType`,
their names consistently represent their Angelscript counterparts (or as close to them without conflict).

## General C++ things
Use [Allman](https://en.wikipedia.org/wiki/Indentation_style#Allman_style)-style braces. Never use `and` and `or` (use `&&` and `||`).
Don't use Hungarian notation (use `The` to label globals to be used by the user, like `TheScriptManager`, or don't label globals as such **when they are inside a namespace**).
Don't use `this->Member` (avoid using `this` whereever possible).