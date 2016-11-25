namespace myExceptions {

	bool ignoreExceptions = false;

	inline void throwNewException(string msg) {
		if (!ignoreExceptions) {
			printf("RAISED NEW EXCEPTION: ");
			puts(msg.c_str());
		}
	}

};
