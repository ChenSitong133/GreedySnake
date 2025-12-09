```mermaid
graph TB
A[Start] --> B[输入控制模式]
B --> C[if 启用]
B --> D[else if 不启用]
B --> E[else if AI控制]
C --> F[设置控制模式为手动]
D --> G[设置控制模式为不启用]
E --> H[设置控制模式为AI]
F --> I[开始游戏]
G --> I
H --> I
```