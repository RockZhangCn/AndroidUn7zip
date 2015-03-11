
#include <jni.h>
#include <android/log.h>
#include "src/xz.h"

static void throwExceptionForZlibError(JNIEnv* env, const char* exceptionClassName, int error) 
{
	/*
    if (error == XZ_MEM_ERROR || XZ_MEMLIMIT_ERROR )
    {
        jniThrowException(env, "java/lang/OutOfMemoryError", NULL);
    }
    else if (error == XZ_OPTIONS_ERROR)
    {
        jniThrowException(env, exceptionClassName, "XZ_OPTIONS_ERROR"); 
    }
    else if (error == XZ_DATA_ERROR)
    {
        jniThrowException(env, exceptionClassName, "XZ_DATA_ERROR");
    }
    else if (error == XZ_FORMAT_ERROR)
    {
        jniThrowException(env, exceptionClassName, "XZ_FORMAT_ERROR");
    }
    else if (error == XZ_BUF_ERROR)
    {
        jniThrowException(env, exceptionClassName, "XZ_BUF_ERROR");
    }
    else    
    {
        jniThrowException(env, exceptionClassName, "Unkown Error");
    }
	*/
}

#undef BUFSIZ
#define BUFSIZ 512

typedef struct XZStream
{
	struct xz_buf b;
	struct xz_dec *s;
    uint8_t in[BUFSIZ];
    uint8_t out[BUFSIZ];
}XZStream;

static struct {
	jclass clazz;
} sJavaGlue;

static XZStream* toNativeXZStream(jlong address) 
{
    return reinterpret_cast<XZStream*>(static_cast<uintptr_t>(address));
}

class XZInflater
{
public:
    static jlong Inflater_createStream(JNIEnv* env, jobject, jboolean noHeader);
    static void Inflater_setInputImpl(JNIEnv* env, jobject, jbyteArray buf, jint off, jint len, jlong handle);
    static jint Inflater_inflateImpl(JNIEnv* env, jobject recv, jbyteArray buf, int off, int len, jlong handle);
    static jint Inflater_getAdlerImpl(JNIEnv*, jobject, jlong handle); 
    static void Inflater_endImpl(JNIEnv*, jobject, jlong handle); 
    static void Inflater_setDictionaryImpl(JNIEnv* env, jobject, jbyteArray dict, int off, int len, jlong handle);
    static void Inflater_resetImpl(JNIEnv* env, jobject, jlong handle);
    static jlong Inflater_getTotalOutImpl(JNIEnv*, jobject, jlong handle);
    static jlong Inflater_getTotalInImpl(JNIEnv*, jobject, jlong handle); 
    static jint Inflater_setFileInputImpl(JNIEnv* env, jobject, jobject javaFileDescriptor, jlong off, jint len, jlong handle);
};

jlong XZInflater::Inflater_createStream(JNIEnv* env, jobject, jboolean noHeader) 
{
	__android_log_print(ANDROID_LOG_ERROR, "ROCKXZ", "createStream was invoked");
	/*
    ALOGE("Inflater_createStream is invoked.");
    UniquePtr<XZStream> jstream(new XZStream);
    if (jstream.get() == NULL) 
    {
        jniThrowException(env, "java/lang/OutOfMemoryError", NULL);
        return -1;
    }

	const int ERROR = -1;

    xz_crc32_init();
#ifdef XZ_USE_CRC64
    xz_crc64_init();
#endif

	jstream -> s = xz_dec_init(XZ_DYNALLOC, 1 << 26);

	if (jstream->s == NULL) {
        throwExceptionForZlibError(env, "java/lang/IllegalArgumentException", XZ_MEM_ERROR);
        return ERROR;
	}

    jstream->b.in = jstream->in;
	jstream->b.in_pos = 0;
	jstream->b.in_size = 0;
	jstream->b.out = jstream->out;
	jstream->b.out_pos = 0;
	jstream->b.out_size = BUFSIZ;

    ALOGE("Inflater_createStream End");
    return reinterpret_cast<uintptr_t>(jstream.release());
	*/
	return 0;
}

void XZInflater::Inflater_setInputImpl(JNIEnv* env, jobject, jbyteArray buf, jint off, jint len, jlong handle) 
{
	/*
    ALOGE("Inflater_setInputImpl is invoked.");
    XZStream * jstream = toNativeXZStream(handle);

    if (buf) 
    {
        jsize size = env->GetArrayLength(buf);
        jbyte* bytes = env->GetByteArrayElements(buf, NULL);
        ALOGE("off is %d, len is %d BUFSIZ is %d, pos is %d", off , len, BUFSIZ, jstream->b.in_pos);

        memcpy((char *)jstream->in + jstream->b.in_pos, (const char *)buf + off , len);
        env->ReleaseByteArrayElements(buf, bytes, 0);
    }
    ALOGE("Inflater_setInputImpl End.");
	*/
}

jint XZInflater::Inflater_setFileInputImpl(JNIEnv* env, jobject, jobject javaFileDescriptor, jlong off, jint len, jlong handle) 
{
#if 0
    NativeZipStream* stream = toNativeXZStream(handle);

    // We reuse the existing native buffer if it's large enough.
    // TODO: benchmark.
    if (stream->inCap < len) 
    {
        stream->setInput(env, NULL, 0, len);
    } else 
    {
        stream->stream.next_in = reinterpret_cast<Bytef*>(&stream->input[0]);
        stream->stream.avail_in = len;
    }

    // As an Android-specific optimization, we read directly onto the native heap.
    // The original code used Java to read onto the Java heap and then called setInput(byte[]).
    // TODO: benchmark.
    int fd = jniGetFDFromFileDescriptor(env, javaFileDescriptor);
    int rc = TEMP_FAILURE_RETRY(lseek(fd, off, SEEK_SET));
    if (rc == -1) 
    {
        jniThrowIOException(env, errno);
        return 0;
    }
    jint totalByteCount = 0;
    Bytef* dst = reinterpret_cast<Bytef*>(&stream->input[0]);
    ssize_t byteCount;
    while ((byteCount = TEMP_FAILURE_RETRY(read(fd, dst, len))) > 0) 
    {
        dst += byteCount;
        len -= byteCount;
        totalByteCount += byteCount;
    }

    if (byteCount == -1) 
    {
        jniThrowIOException(env, errno);
        return 0;
    }
    return totalByteCount;
#endif
    return 0;
}

//buf store the decompressed data.
jint XZInflater::Inflater_inflateImpl(JNIEnv* env, jobject recv, jbyteArray buf, int off, int len, jlong handle) 
{
	/*
    ALOGE("Inflater_inflateImpl is invoked.");
    XZStream * jstream = toNativeXZStream(handle);

    ScopedByteArrayRW out(env, buf);
    if (out.get() == NULL) {
        return -1;
    }

    jstream->b.out = reinterpret_cast<uint8_t *>(out.get());
    jstream->b.out_pos = off;
    jstream->b.out_size = len;

    size_t initialNextIn = jstream->b.in_pos;
    size_t initialNextOut = jstream->b.out_pos;

    enum xz_ret ret = xz_dec_run(jstream->s, &jstream->b);

    switch (ret) 
    {
        case XZ_OK:
            break;
        case XZ_STREAM_END:
            static jfieldID finished = env->GetFieldID(sJavaGlue.clazz, "finished", "Z");
            env->SetBooleanField(recv, finished, JNI_TRUE);

            xz_dec_end(jstream->s);
            jstream->s = NULL;
            break;

        case XZ_MEM_ERROR:
        case XZ_MEMLIMIT_ERROR:
        case XZ_OPTIONS_ERROR:
        case XZ_DATA_ERROR:
        case XZ_FORMAT_ERROR:
        case XZ_BUF_ERROR:
            throwExceptionForZlibError(env, "java/util/zip/DataFormatException", ret);
            return -1;
        default:
            return 0;
    }

    jint bytesRead = jstream->b.in_pos - initialNextIn;
    jint bytesWritten = jstream->b.out_pos - initialNextOut;

    static jfieldID inReadField = env->GetFieldID(sJavaGlue.clazz, "inRead", "I");
    jint inReadValue = env->GetIntField(recv, inReadField);
    inReadValue += bytesRead;
    env->SetIntField(recv, inReadField, inReadValue);
    ALOGE("Inflater_inflateImpl End.");
    return bytesWritten;

#if 0
    NativeZipStream* stream = toNativeZipStream(handle);
    ScopedByteArrayRW out(env, buf);
    if (out.get() == NULL) {
        return -1;
    }
    stream->stream.next_out = reinterpret_cast<Bytef*>(out.get() + off);
    stream->stream.avail_out = len;

    Bytef* initialNextIn = stream->stream.next_in;
    Bytef* initialNextOut = stream->stream.next_out;

    int err = inflate(&stream->stream, Z_SYNC_FLUSH);
    switch (err) {
    case Z_OK:
        break;
    case Z_NEED_DICT:
        static jfieldID needsDictionary = env->GetFieldID(JniConstants::inflaterClass, "needsDictionary", "Z");
        env->SetBooleanField(recv, needsDictionary, JNI_TRUE);
        break;
    case Z_STREAM_END:
        static jfieldID finished = env->GetFieldID(JniConstants::inflaterClass, "finished", "Z");
        env->SetBooleanField(recv, finished, JNI_TRUE);
        break;
    case Z_STREAM_ERROR:
        return 0;
    default:
        throwExceptionForZlibError(env, "java/util/zip/DataFormatException", err);
        return -1;
    }

    jint bytesRead = stream->stream.next_in - initialNextIn;
    jint bytesWritten = stream->stream.next_out - initialNextOut;

    static jfieldID inReadField = env->GetFieldID(JniConstants::inflaterClass, "inRead", "I");
    jint inReadValue = env->GetIntField(recv, inReadField);
    inReadValue += bytesRead;
    env->SetIntField(recv, inReadField, inReadValue);
    return bytesWritten;
#endif
	//sJavaGlue.clazz = (jclass)env->NewGlobalRef(clazz);
	//jclass inflaterClass = env->FindClass("com/tencent/smtt/webkit/CacheManager$CacheResult");
	*/
	return 0;
}

jint XZInflater::Inflater_getAdlerImpl(JNIEnv*, jobject, jlong handle) 
{
#if 0
    return toNativeXZStream(handle)->stream.adler;
#endif
    return 0;
}

void XZInflater::Inflater_endImpl(JNIEnv*, jobject, jlong handle) 
{
	/*
    ALOGE("Inflater_endImpl is invoked.");
    XZStream * jstream = toNativeXZStream(handle);
    xz_dec_end(jstream ->s);
    delete jstream;
    ALOGE("Inflater_endImpl End.");
	*/
}

void XZInflater::Inflater_setDictionaryImpl(JNIEnv* env, jobject, jbyteArray dict, int off, int len, jlong handle) 
{
#if 0
    toNativeXZStream(handle)->setDictionary(env, dict, off, len, true);
#endif
}

void XZInflater::Inflater_resetImpl(JNIEnv* env, jobject, jlong handle) 
{
	/*
    ALOGE("Inflater_resetImpl is invoked.");
    XZStream * jstream = toNativeXZStream(handle);
    xz_dec_reset(jstream -> s);
	*/
}

jlong XZInflater::Inflater_getTotalOutImpl(JNIEnv*, jobject, jlong handle) 
{
	/*
    ALOGE("Inflater_getTotalOutImpl is invoked.");
    XZStream * jstream = toNativeXZStream(handle);
    return jstream->b.out_size - jstream->b.out_pos;
	*/
	return 0l;
}

jlong XZInflater::Inflater_getTotalInImpl(JNIEnv*, jobject, jlong handle) 
{
	/*
    ALOGE("Inflater_getTotalInImpl is invoked.");
    XZStream * jstream = toNativeXZStream(handle);
    return jstream->b.in_size - jstream->b.in_pos;
	*/
	return 0l;
}

static const JNINativeMethod methods_table[] = 
{
    {"createStream", "(Z)J", (void *)&XZInflater::Inflater_createStream},
    {"endImpl", "(J)V", (void *)&XZInflater::Inflater_endImpl},
    {"getAdlerImpl", "(J)I", (void *)&XZInflater::Inflater_getAdlerImpl},
    {"getTotalInImpl", "(J)J", (void *)&XZInflater::Inflater_getTotalInImpl},
    {"getTotalOutImpl", "(J)J", (void *)&XZInflater::Inflater_getTotalOutImpl},
    {"inflateImpl", "([BIIJ)I", (void *)&XZInflater::Inflater_inflateImpl},
    {"resetImpl", "(J)V", (void *)&XZInflater::Inflater_resetImpl},
    {"setDictionaryImpl", "([BIIJ)V", (void *)&XZInflater::Inflater_setDictionaryImpl},
    {"setFileInputImpl", "(Ljava/io/FileDescriptor;JIJ)I", (void *)&XZInflater::Inflater_setFileInputImpl},
    {"setInputImpl", "([BIIJ)V", (void *)&XZInflater::Inflater_setInputImpl},
};

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;

	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return result;
	}

	env->RegisterNatives(env->FindClass("com/tencent/smtt/util/Inflater"), methods_table, sizeof(methods_table)/sizeof(methods_table[0]));

	return JNI_VERSION_1_4;
}


/*

int register_xz_decompress_android(JNIEnv* env) 
{
	jclass clazz = env->FindClass("com/tencent/smtt/util/Inflater");
	sJavaGlue.clazz = (jclass)env->NewGlobalRef(clazz);

	return env->RegisterNatives(clazz, XZInflaterNativeMethods, sizeof(XZInflaterNativeMethods) / sizeof(XZInflaterNativeMethods[0]));
}
*/
