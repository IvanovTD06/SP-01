# libzstd - Zstandard lossless compression algorithm

This is a `build2` package for the
[`zstd`](https://https://github.com/facebook/zstd) C library. It provides a
fast lossless compression algorithm, targeting real-time compression scenarios
at `zlib`-level and better compression ratios. Zstandard's format is stable
and documented in [RFC8878](https://datatracker.ietf.org/doc/html/rfc8878).


## Usage

To start using `libzstd` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libzstd ^1.5.5
```

Then import the library in your `buildfile`:

```
import libs = libzstd%lib{zstd}
```

Note also that the `lib{zstd}` library provides `build2` metadata that
describes its configuration:

```
lib{zstd}:
{
  libzstd.multithread = [bool] true
}
```
