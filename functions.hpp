const auto cache_address = rebase(0x82BED0); // Put your rebase function instead of 'rebase', also the address might not be accurate so you'd have to give me a bit
const auto cache_function = reinterpret_cast<void*>(cache_address); // DEREFERENCE
const auto cache_call = reinterpret_cast<void(__fastcall*)(lua_State*, void*)>(cache_address); // Define our function

int clone_ref(lua_State* state)
{
	luaL_checktype(state, 1, LUA_TUSERDATA);

	// Retrieve the original userdata from the Lua stack
	const auto original_userdata = lua_touserdata(state, 1);

	// Dereference the pointer to retrieve the actual data stored in the userdata
	const auto returned_userdata = *reinterpret_cast<std::uintptr_t*>(original_userdata);

	lua_pushlightuserdata(state, cache_function); // Push the cache function onto the stack

	lua_rawget(state, -10000); // Retrieve the cache function from the registry
	lua_pushlightuserdata(state, reinterpret_cast<void*>(returned_userdata)); // Push the returned userdata onto the stack as a key
	lua_rawget(state, -2); // Retrieve the value associated with the returned userdata from the cache

	lua_pushlightuserdata(state, reinterpret_cast<void*>(returned_userdata)); // Push the returned userdata onto the stack as a key
	lua_pushnil(state); // Push `nil` onto the stack as a value
	lua_rawset(state, -4); // Remove the value associated with the returned userdata from the cache

	// Call the cache function, passing the original userdata as an argument
	cache_call(state, original_userdata);

	lua_pushlightuserdata(state, reinterpret_cast<void*>(returned_userdata)); // Push the returned userdata onto the stack as a key
	lua_pushvalue(state, -3); // Push the result of the cache call onto the stack as a value
	lua_rawset(state, -5); // Set the value stored at the `returned_userdata` lightuserdata object in the `engine_update::functions::cache_function` table to the value stored at the top of the stack.

	// Return 1 to indicate that one value has been returned to Luau
	return 1;
}

int compare_instances(lua_State* state)
{
	const auto compared_instance = *reinterpret_cast<std::uintptr_t*>(lua_touserdata(state, 1)) == *reinterpret_cast<std::uintptr_t*>(lua_touserdata(state, 2));
	lua_pushboolean(state, compared_instance);

  // Return 1 value exactly which is the compared instance's results
	return 1;
}
