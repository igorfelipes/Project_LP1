# Sistema de gerenciamento de Chamados

Projeto da disciplina de Linguagem de Programação I apresentado a professora do curso de Sistemas de Informação como requisito parcial 
para a obtenção da segunda nota do semestre 2019.2 .

## Autores

- Igor Felipe Sales
- Rodrigo Henrique Soares de Oliveira Andrade

## Descrição do Projeto

 A administração correta de uma empresa passa por uma série de fatores e o gerenciamento de chamados é um deles. Um chamado é uma notificação de problema que o usuário faz para um responsável a fim de resolver o seu problema. Centralizar todas as solicitações de atendimento em um único lugar permite que seja possível acompanhar e solucionar os chamados em aberto em um tempo mais curto.  
  
  
 Assim como outras empresas, a Alana’s Corporation atende aos chamados respeitando diversos níveis operacionais: 1) atendimento virtual (mensagem ou chamada de voz), 2) atendimento remoto e 3) visita de um técnico.  
  Os processos podem apresentar os seguintes status: Em aberto, Em atendimento, Em atendimento - visita técnica, Concluído, Não resolvido.  
  
  
 O sistema terá dois módulos principais: módulo do cliente e o módulo do gerente de tecnologia. O cliente terá como funcionalidades a criação e remoção de chamados e o acompanhamento dos mesmos. Enquanto isso, o gerente de tecnologia tem como funcionalidades o acompanhamento dos chamados, mudança de status dos chamados, geração de relatórios e agendamento de visitas técnicas.  

### Funcionalidades Cliente:
- Criar chamados.
- Tipos de chamado:
 - Chamados relacionados à Internet: considerações relacionadas à
problemas de conexão e acesso, etc.
 - Chamados relacionados à serviços de rede: dispositivos de rede,
problemas em serviço de segurança, etc.
- Informações necessárias: título do chamado, descrição, data e autoria.
- Enviar mensagens de feedback para a equipe ao longo do processo.

### Funcionalidades Gerente de rede:
- Visualizar os chamados abertos e finalizados
- Enviar mensagens para os clientes
- Mudar o status dos chamados:  
     - Em aberto (0): Status inicial e deve permanecer caso o chamado não
    seja lido.  
     - Em atendimento (1) : Quando o chamado for lido, o status mudará para
    o presente status. Em casos de atendimento virtual, o chamado deve permanecer
    nesta categoria.  
     - Em atendimento - visita técnica (2) : Quando o gerente julgar
    necessário um atendimento técnico ele deve enquadrar o processo neste status.  
     - Concluído (3) : Quando o processo for concluído.  
     - Não resolvido (4) : Quando não há soluções previstas.  
- Agendar visitas técnicas.  
- Gerar relatórios sobre os chamados  
