import { useState, useEffect } from "react";
import { motion } from "framer-motion";
import { Search, Edit, Trash2 } from "lucide-react";
import { useNavigate } from "react-router-dom";


const ClientsTable = ({ totalClients }) => {
    const [searchTerm, setSearchTerm] = useState("");
    const [filteredClients, setFilteredClients] = useState(totalClients);
    const navigate = useNavigate();

    useEffect(() => {
        setFilteredClients(totalClients);  // Sincroniza el estado al recibir los productos
    }, [totalClients]);

    const handleSearch = (e) => {
        const term = e.target.value.toLowerCase();
        setSearchTerm(term);
        const filtered = totalClients.filter(
            (client) => client.nombre.toLowerCase().includes(term) || client.cuit.toLowerCase().includes(term) || client.razon_social.toLowerCase().includes(term)
        );
        setFilteredClients(filtered);
    };

    const deleteClient = async (id) => {
        try {
            const response = await fetch(`http://localhost:9080/clientes/${id}`, {
                method: 'DELETE',
            });

            if (response.ok) {
                alert('Cliente eliminado con éxito');
                setFilteredClients(filteredClients.filter(client => client.id !== id));
            } else {
                alert('Error al eliminar el cliente');
            }
        } catch (error) {
            console.error('Error al eliminar el cliente:', error);
        }
    };

    const handleEdit = (client) => {
        navigate('/edit-client', { state: { client } }); // Navegar con los datos del cliente
    };

    return (
        <motion.div
            className='bg-gray-800 bg-opacity-50 backdrop-blur-md shadow-lg rounded-xl p-6 border border-gray-700 mb-8'
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ delay: 0.2 }}
        >
            <div className="flex justify-between items-center mb-6">
                <h2 className="text-x1 font-semibold text-gray-100">Product List</h2>
                <div className="relative">
                    <input
                        type="text"
                        placeholder="Search products"
                        className="bg-gray-700 text-white placeholder-gray-400 rounded-lg pl-10 pr-4 py-2 focus:outline-none focus:ring-2 focus:ring-blue-500"
                        onChange={handleSearch}
                        value={searchTerm}
                    />
                    <Search className='absolute left-3 top-2.5 text-gray-400' size={18} />
                </div>
            </div>

            <div className="overflow-x-auto">
                <table className="min-w-full divide-y divide-gray-700">
                    <thead>
                        <tr>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Id
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Nombre
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Razon Social
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                CUIT
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Tributacion
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Email
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Telefono
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Whatsapp
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Direccion Fiscal
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Direccion Entrega
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Localidad
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Codigo Postal
                            </th>
                            <th className='px-6 py-3 text-left text-xs font-medium text-gray-400 uppercase tracking-wider'>
                                Actions
                            </th>
                        </tr>
                    </thead>

                    <tbody className="divide-y divide-gray-700">
                        {filteredClients.map((client) => (
                            <motion.tr 
                                key={client.id}
                                initial={{opacity:0}}
                                animate={{opacity:1}}
                                transition={{duration:0.3}}
                            >
                                <td className="px-6 py-4 whitespace-nowrap">
                                    <div className="text-sm font-medium text-gray-100">{client.id}</div>
                                </td>
                                <td className='px-6 py-4 whitespace-nowrap'>
									<div className='text-sm text-gray-300'>{client.nombre}</div>
								</td>
								<td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.razon_social}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.cuit}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.tributacion}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.email}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.telefono}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.whatsapp}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.direccion_fiscal}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.direccion_entrega}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.localidad}</div>
								</td>
                                <td className='px-6 py-4 whitespace-nowrap'>
                                    <div className='text-sm text-gray-300'>{client.cp}</div>
								</td>

								<td className='px-6 py-4 whitespace-nowrap text-sm text-gray-300'>
                                    <button 
                                        className="text-indigo-400 hover:text-indigo-300 mr-2"
                                        onClick={() => handleEdit(client)}
                                    >
                                        <Edit size={18} />
                                    </button>
                                    <button 
                                        className="text-red-400 hover:text-red-300"
                                        onClick={() => deleteClient(client.id)}
                                    >
                                        <Trash2 size={18} />
                                    </button>
								</td>
                            </motion.tr>
                        ))}
                    </tbody>
                </table>
            </div>
        </motion.div>
    );
};

export default ClientsTable;