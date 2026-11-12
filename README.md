# redis-clone

A Redis-compatible in-memory key-value server, built from scratch in modern C++.

## Goal

A Redis-compatible in-memory key-value server written from scratch in modern C++ (C++20). It speaks the Redis Serialization Protocol (RESP), so the official `redis-cli` and existing Redis client libraries can connect to it with no changes. It supports the core string commands (`PING`, `ECHO`, `SET`, `GET`, `DEL`, `EXISTS`, `INCR`), key expiration (`EXPIRE`, `TTL`), handles many clients at once, and saves data to disk so it survives a restart. The project is for learning how databases and network servers work inside, using only the C++ standard library and POSIX system calls.

**Done means:** `redis-cli` can connect, run every supported command with the same responses as real Redis, and `redis-benchmark` runs against it without errors. All of this is covered by automated tests that run in CI.

## Scope

### Must have
- TCP server on port 6379
- RESP parser and serializer
- Commands: `PING`, `ECHO`, `SET`, `GET`, `DEL`, `EXISTS`, `INCR`
- Key expiration: `SET ... EX/PX`, `EXPIRE`, `TTL`
- Multiple concurrent clients
- Persistence (append-only file)
### Nice to have
- Lists, hashes, sets (and sorted sets)
- RDB snapshots
- Pub/Sub (`SUBSCRIBE`, `PUBLISH`)
- Transactions (`MULTI`, `EXEC`, `DISCARD`)
- Event loop with `epoll` / `kqueue`
- Primary-replica replication
### Won't do
- Clustering and sharding
- Lua scripting
- Authentication and ACLs
- Full compatibility with every Redis command
## Roadmap

| Milestone | Description | Release | Status |
|---|---|---|---|
| M1 | TCP server + RESP, `PING` / `ECHO` | v0.1.0 | ⬜ |
| M2 | Core key-value store, concurrent clients | v0.2.0 | ⬜ |
| M3 | Key expiration | v0.3.0 | ⬜ |
| M4 | Data types (lists, hashes, sets) | v0.4.0 | ⬜ |
| M5 | Persistence (AOF, then RDB) | v0.5.0 | ⬜ |
| M6 | Pub/Sub + transactions | v0.6.0 | ⬜ |
| M7 | Replication (stretch) | v0.7.0 | ⬜ |
| M8 | Benchmarks, Docker, docs | v1.0.0 | ⬜ |

## Getting started

> _To be written once the build is set up (M1)._

```bash
# build
 
# run
 
# test
```

## Usage

> _To be written: example `redis-cli` session._

## Architecture

> _To be written: see `docs/ARCHITECTURE.md` once it exists._

## Benchmarks

> _To be written: `redis-benchmark` results vs. real Redis (M8)._

## Contributing / workflow

- `main` is protected; all changes go through pull requests.
- Branches: `feat/<issue>-<name>`, `fix/<issue>-<name>`, `docs/...`, `test/...`, `chore/...`
- Commits follow [Conventional Commits](https://www.conventionalcommits.org/).
- CI must pass before merging; PRs are squash-merged.
## License

