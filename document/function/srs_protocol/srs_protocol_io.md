# srs_protocol_io

## Framework
```
 * The system io reader/writer architecture:
 *                                         +---------------+  +---------------+
 *                                         | IStreamWriter |  | IVectorWriter |
 *                                         +---------------+  +---------------+
 *                                         | + write()     |  | + writev()    |
 *                                         +-------------+-+  ++--------------+
 * +----------+     +--------------------+               /\   /\
 * | IReader  |     |    IStatistic      |                 \ /
 * +----------+     +--------------------+                  V
 * | + read() |     | + get_recv_bytes() |           +------+----+
 * +------+---+     | + get_send_bytes() |           |  IWriter  |
 *       / \        +---+--------------+-+           +-------+---+
 *        |            / \            / \                   / \
 *        |             |              |                     |
 * +------+-------------+------+      ++---------------------+--+
 * | IProtocolReader           |      | IProtocolWriter         |
 * +---------------------------+      +-------------------------+
 * | + readfully()             |      | + set_send_timeout()    |
 * | + set_recv_timeout()      |      +-------+-----------------+
 * +------------+--------------+             / \
 *             / \                            |
 *              |                             |
 *           +--+-----------------------------+-+
 *           |       IProtocolReadWriter        |
 *           +----------------------------------+
```


```
 *           +--+-----------------------------+-+
 *           |       IProtocolReadWriter        |
 *           +----------------------------------+
                               / \
                                |
                                |
 *           +--+-----------------------------+-+
 *           |       SrsTcpConnection        |
 *           +----------------------------------+
```