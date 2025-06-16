		# Pacman

**Trabalho 3 - INF 110**

Este repositório é dedicado ao desenvolvimento do nosso projeto de Pacman para a disciplina INF 110.

---

## Guia Rápido de Git para o Nosso Projeto

Bem-vindos ao repositório do nosso trabalho! Este guia rápido cobre as operações essenciais do Git que usaremos para colaborar de forma eficiente. Entender esses comandos básicos é fundamental para o sucesso do projeto.

---

### 1. Clonando o Repositório (Primeiro Acesso)

Para começar, clone o repositório para ter uma cópia local do projeto na sua máquina:

```bash
git clone <URL_DO_REPOSITÓRIO>
```

**Exemplo:**

```bash
git clone https://github.com/NicolasSalvador13/Pacman.git
```

---

### 2. Verificando o Status

Sempre verifique o status do seu repositório local antes de fazer qualquer alteração. Isso mostra arquivos modificados, arquivos prontos para commit e em qual *branch* você está.

```bash
git status
```

---

### 3. Adicionando Arquivos para Commit

Após fazer suas alterações, "prepare" os arquivos para o próximo *commit*. Isso indica ao Git quais mudanças você quer incluir na próxima versão.

Para adicionar um arquivo específico:

```bash
git add nome-do-arquivo.extensao
```

Para adicionar todos os arquivos modificados e novos:

```bash
git add .
```

---

### 4. Salvando Alterações (Commit)

Um *commit* é como um "ponto de salvamento" no histórico do projeto. Ele registra as alterações preparadas (`git add`) com uma mensagem descritiva.

```bash
git commit -m "Sua mensagem descritiva sobre as alterações"
```

**Exemplo:**

```bash
git commit -m "Adiciona estrutura inicial do projeto e README"
```

---

### 5. Baixando Alterações do Repositório Remoto (Pull)

**Antes de começar a trabalhar** ou periodicamente, sempre puxe as últimas alterações do repositório remoto (GitHub) para sua máquina. Isso garante que você esteja com a versão mais atualizada e evita conflitos.

```bash
git pull origin <nome-da-branch>
```

**Exemplo:** Se você está na *branch* `main`:

```bash
git pull origin main
```

---

### 6. Enviando Suas Alterações para o Repositório Remoto (Push)

Após commitar suas alterações localmente, envie-as para o repositório remoto (GitHub) para que o restante do grupo possa acessá-las.

```bash
git push origin <nome-da-branch>
```

**Exemplo:** Se você está na *branch* `feature-login`:

```bash
git push origin feature-login
```

---

### 7. Trabalhando com Branches (Galhos)

*Branches* são cruciais para o trabalho em grupo. Elas permitem que você desenvolva novas funcionalidades ou corrija *bugs* de forma isolada, sem impactar a versão principal do projeto.

#### 7.1. Verificando as Branches Existentes

Para ver as *branches* locais e qual está ativa:

```bash
git branch
```

#### 7.2. Criando uma Nova Branch

Crie uma nova *branch* para cada funcionalidade ou tarefa. Use nomes descritivos!

```bash
git branch nome-da-sua-branch
```

**Exemplo:**

```bash
git branch feature/cadastro-usuario
```

#### 7.3. Alternando entre Branches (Checkout)

Para mudar para uma *branch* existente e começar a trabalhar nela:

```bash
git checkout nome-da-sua-branch
```

**Exemplo:**

```bash
git checkout feature/cadastro-usuario
```

**Dica:** Você pode criar e mudar para uma nova *branch* com um único comando:

```bash
git checkout -b nome-da-sua-branch
```

**Exemplo:**

```bash
git checkout -b feature/validacao-forms
```

#### 7.4. Excluindo uma Branch (Localmente)

Após o trabalho em uma *branch* ser concluído e suas alterações incorporadas à `main` (ou outra *branch* principal), você pode excluí-la localmente.

```bash
git branch -d nome-da-sua-branch
```

**Exemplo:**

```bash
git branch -d feature/cadastro-usuario
```

#### 7.5. Enviando uma Nova Branch para o Repositório Remoto

Se você quer que sua nova *branch* apareça no GitHub para colaboração:

```bash
git push origin nome-da-sua-branch
```

---

### 8. Fusão de Branches (Merge)

Quando o trabalho em uma *branch* de funcionalidade está pronto, ele precisa ser mesclado (*merged*) na *branch* principal (geralmente `main`). Isso integra suas alterações à linha principal de desenvolvimento.

1.  **Primeiro, mude para a *branch* principal** (onde você quer incorporar as mudanças):
    ```bash
    git checkout main
    ```
2.  **Puxe as últimas atualizações da *branch* principal** antes de mesclar:
    ```bash
    git pull origin main
    ```
3.  **Faça o *merge* da sua *branch* de funcionalidade na *branch* principal:**
    ```bash
    git merge nome-da-sua-branch
    ```
4.  **Envie as alterações mescladas para o repositório remoto:**
    ```bash
    git push origin main
    ```

---

## Dicas Importantes para o Grupo

* **Puxe antes de trabalhar:** Sempre execute `git pull` na sua *branch* antes de começar a codificar.
* **Comite com frequência:** Faça *commits* pequenos e focados. Isso facilita a revisão e a identificação de problemas.
* **Mensagens de commit claras:** Explique o *porquê* das suas mudanças, não apenas *o quê*.
* **Use *branches*:** Nunca trabalhe diretamente na *branch* `main`. Crie uma *branch* específica para cada nova funcionalidade ou correção.
* **Comunicação:** Se tiver dúvidas ou enfrentar conflitos, **comunique-se** imediatamente com o grupo!

---

Com este guia, esperamos que todos se sintam mais confiantes usando o Git para colaborar no nosso projeto. Boa sorte com o trabalho!

---
