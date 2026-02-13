
moduleHandle moduleFn(load)(const char* modulePath){
	nonull(modulePath) return nil;

	c16* modulePathWide = alloca(strnlen(modulePath, MAX_COMMAND_LEN));

	std.String.Encoding.UTF8.toUtf16(
		generic modulePath, MAX_COMMAND_LEN, 
		modulePathWide,     MAX_COMMAND_LEN
	);

	var result = LoadLibraryW(generic modulePathWide);

return result ? result : ({
		ERR(ERR.FAIL, "Failed to run command");
		var errmsg = WinLib.Error.getMsg(GetLastError());

		printlnErr("Error Info: ", $(errmsg));

		WinLib.Error.freeMsg(errmsg);

		nil;
});
}

pntr moduleFn(symbol)(moduleHandle handle, const char* symbol){
	nonull(handle, symbol) return nil;

return GetProcAddress(generic handle, symbol);
}

errvt moduleFn(unload)(moduleHandle handle){
	nonull(handle) return err;

return FreeLibrary(generic handle) ? OK : 
({
	var err    = ERR(ERR.FAIL, "Failed to run command");
	var errmsg = WinLib.Error.getMsg(GetLastError());

	printlnErr("Error Info: ", $(errmsg));

	WinLib.Error.freeMsg(errmsg);

	err;
});
}
