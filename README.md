# Pacman
Trabalho 3 - INF 110

Repositório para trabalho em grupo

Guia Rápido de Git para o Nosso Projeto
Bem-vindos ao repositório do nosso trabalho! Este README serve como um guia rápido para as principais operações do Git que usaremos. O Git é uma ferramenta poderosa para controle de versão, e entender esses comandos básicos nos ajudará a trabalhar de forma colaborativa e eficiente.

1. Clonando o Repositório (Primeiro Acesso)
  Se você ainda não tem o projeto na sua máquina, o primeiro passo é clonar o repositório. Isso cria uma cópia local de todo o histórico do projeto.
  
  git clone <URL_DO_REPOSITÓRIO>
  Exemplo:
  git clone (https://github.com/NicolasSalvador13/Pacman)[https://github.com/NicolasSalvador13/Pacman]

2. Verificando o Status (Status)
  Antes de fazer qualquer alteração, é sempre bom verificar o status do seu repositório local. Isso mostra quais arquivos foram modificados, quais estão prontos para serem "commitados" e em qual branch você está.
  
  git status

3. Adicionando Arquivos para Commit (Add)
  Depois de fazer alterações nos seus arquivos, você precisa "prepará-los" para o próximo commit. Isso diz ao Git quais alterações você quer incluir na próxima versão.
  
  Para adicionar um arquivo específico:
  git add nome-do-arquivo.extensao
  
  Para adicionar todos os arquivos modificados e novos:
  git add .

4. Salvando Alterações (Commit)
  Um "commit" é como um ponto de salvamento. Ele registra as alterações preparadas (git add) no histórico do projeto, junto com uma mensagem que descreve o que você fez.
  
  git commit -m "Sua mensagem descritiva sobre as alterações"
  Exemplo:
  git commit -m "Adiciona a estrutura inicial do projeto e README"

5. Baixando Alterações do Repositório Remoto (Pull)
  Antes de começar a trabalhar ou depois de um tempo, é crucial puxar as últimas alterações do repositório remoto (GitHub) para a sua máquina. Isso garante que você esteja trabalhando com a versão mais atualizada do código e evita conflitos.
  
  git pull origin <nome-da-branch>
  Exemplo: Se você está na branch main:
  
  git pull origin main

6. Enviando Suas Alterações para o Repositório Remoto (Push)
  Depois de commitar suas alterações localmente, você precisa enviá-las para o repositório remoto (GitHub) para que o restante do grupo possa vê-las e utilizá-las.
  
  git push origin <nome-da-branch>
  Exemplo: Se você está na branch feature-login:
  git push origin feature-login

7. Trabalhando com Branches (Galhos)
  Branches são essenciais para o trabalho em grupo. Elas permitem que você desenvolva novas funcionalidades ou corrija bugs isoladamente, sem afetar a versão principal do projeto.

7.1. Verificando as Branches Existentes
  Para ver quais branches existem no seu repositório local e qual você está usando atualmente:
  
  git branch

7.2. Criando uma Nova Branch
  Crie uma nova branch para trabalhar em uma funcionalidade específica ou tarefa. Use nomes descritivos!
  
  git branch nome-da-sua-branch
  Exemplo:
  
  git branch feature/cadastro-usuario

7.3. Alternando entre Branches (Checkout)
  Para mudar para uma branch existente e começar a trabalhar nela:
  
  git checkout nome-da-sua-branch
  Exemplo:
  git checkout feature/cadastro-usuario
  Dica: Você pode criar e já mudar para uma nova branch com um único comando:
  
  git checkout -b nome-da-sua-branch
  Exemplo:
  git checkout -b feature/validacao-forms

7.4. Excluindo uma Branch (Localmente)
  Depois que o trabalho em uma branch for concluído e suas alterações forem incorporadas à main (ou outra branch principal), você pode excluí-la localmente.
  
  git branch -d nome-da-sua-branch
  Exemplo:
  git branch -d feature/cadastro-usuario
  
  7.5. Enviando uma Nova Branch para o Repositório Remoto
  Se você criou uma nova branch e quer que ela apareça no GitHub para que outros possam vê-la ou colaborar:
  
  git push origin nome-da-sua-branch

8. Fusão de Branches (Merge)
  Quando o trabalho em uma branch de funcionalidade está pronto, ele precisa ser "mesclado" (merged) na branch principal (geralmente main ou master). Isso integra as alterações da sua branch na linha principal de desenvolvimento.
  
  Primeiro, mude para a branch onde você quer incorporar as mudanças (geralmente main):
  git checkout main
  
  Puxe as últimas atualizações da branch principal para garantir que você esteja com a versão mais recente antes de mesclar:
  git pull origin main
  
  Faça o merge da sua branch de funcionalidade na branch principal:
  git merge nome-da-sua-branch
  
  Envie as alterações mescladas para o repositório remoto:
  git push origin main


Dicas Importantes para o Grupo:

  Puxe antes de trabalhar: Sempre faça um git pull na sua branch antes de começar a codificar para garantir que você tem as últimas alterações.
  
  Comite com frequência: Faça commits pequenos e bem definidos. Isso facilita a revisão e a identificação de problemas.
  
  Mensagens de commit claras: Escreva mensagens de commit que expliquem o porquê das suas mudanças, não apenas o o quê.
  
  Use branches: Não trabalhe diretamente na branch main. Crie uma branch para cada nova funcionalidade ou correção.
  
  Comunicação: Se tiver dúvidas ou enfrentar conflitos, comunique-se com o grupo!
  
  Com este guia, esperamos que todos se sintam mais confortáveis usando o Git para colaborar no nosso projeto. Boa sorte com o trabalho!
