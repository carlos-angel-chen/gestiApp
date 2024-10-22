import React, { useState, useEffect } from 'react';
import { motion } from 'framer-motion';
import { useNavigate } from 'react-router-dom';

const AddSaleForm = () => {
    // PRODUCTO
    const [sku, setSku] = useState('');
    const [producto, setProducto] = useState([]);
    const [cantidad, setCantidad] = useState({});
    const [carrito, setCarrito] = useState([]);
    const [pedidoId, setPedidoId] = useState(0);
    // CLIENTE
    const [cuit, setCuit] = useState('');
    const [clientes, setClientes] = useState([]);
    const [clienteSeleccionado, setClienteSeleccionado] = useState(null);
    // LOGISTICA
    const [logisticas, setLogisticas] = useState([]);
    const [logisticaSeleccionada, setLogisticaSeleccionada] = useState(null);
    // METODO DE PAGO
    const [metodoPagos, setMetodoPagos] = useState([]);
    const [metodoPagoSeleccionado, setMetodoPagoSeleccionado] = useState(null);
    // OBSERVACIONES
    const [observaciones, setObservaciones] = useState('');
    // TOTAL
    const [subTotal, setSubTotal] = useState(0);
    const [descuento, setDescuento] = useState(0);
    const [total, setTotal] = useState(0);

    const navigate = useNavigate();
    
    const ColoredLine = ({ color }) => (
        <hr
            style={{
                color: color,
                backgroundColor: color,
                height: 5
            }}
        />
    );

    const fetchProductoBySku = async () => {
        try {
        const response = await fetch(`http://localhost:9080/productos/sku/${sku}`);
        const productos = await response.json();
        // Manejamos el resultado del producto
        setProducto(productos);
        } catch (error) {
            console.error('Error al obtener el producto:', error);
        }
    };

    const handleCantidadChange = (id, newCantidad) => {
        if (newCantidad > 0 && newCantidad <= producto.find((p) => p.id === id).stock_actual) {
            setCantidad((prevCantidad) => ({ ...prevCantidad, [id]: newCantidad }));
        }
    };

    const agregarAlCarrito = (producto) => {
        const cantidadProducto = cantidad[producto.id] || 1;
        const productoExistente = carrito.find((item) => item.id === producto.id);

        if (productoExistente) {
            setCarrito((prevCarrito) =>
            prevCarrito.map((item) =>
                item.id === producto.id ? { ...item, cantidad: item.cantidad + cantidadProducto } : item
            )
            );
        } else {
            setCarrito((prevCarrito) => [...prevCarrito, { ...producto, cantidad: cantidadProducto }]);
        }
        actualizarSubtotal();
    };
    
    const actualizarSubtotal = () => {
        const subtotal = carrito.reduce((acc, item) => acc + item.cantidad * item.precio_venta, 0);
        setSubTotal(subtotal);
        setTotal(subtotal - descuento);
    };

    const aplicarDescuento = () => {
        const descuentoAplicado = parseFloat(descuento) || 0; // Convertir el valor a float.
    
        if (isNaN(descuentoAplicado) || descuentoAplicado < 0) {
            alert('Por favor, ingrese un valor de descuento válido.');
            return;
        }
        setDescuento(descuentoAplicado);
        setTotal(subTotal - descuentoAplicado);
    };

    const verificarCliente = async () => {
        try {
            const response = await fetch(`http://localhost:9080/clientes/cuit/${cuit}`);
            const cliente = await response.json();
            setClientes(cliente);
        } catch (error) {
            console.error('Error al verificar cliente:', error);
        }
    };

    const getLogistica = async () => {
        try{
            const response = await fetch('http://localhost:9080/logistica');
            const logisticas = await response.json();
            setLogisticas(logisticas);
        } catch (error) {
            console.error('Error al obtener las logisticas:', error);
        }
    };

    const getMetodoPago = async () => {
        try{
            const response = await fetch('http://localhost:9080/metodo_pagos');
            const metodoPagos = await response.json();
            setMetodoPagos(metodoPagos);
        } catch (error) {
            console.error('Error al obtener los metodos de pago:', error);
        }
    };

    const getMaxPedidoId = async () => {
        try{
            const response = await fetch('http://localhost:9080//calculus/max_pedido_id');
            const maxPedidoId = await response.json();
            setPedidoId(parseInt(maxPedidoId.maxPedidoId));
        } catch (error) {
            console.error('Error al obtener el id del pedido:', error);
        }
    };

    const formatearFecha = (fecha) => {
        const year = fecha.getFullYear();
        const month = String(fecha.getMonth() + 1).padStart(2, '0'); // Mes empieza desde 0
        const day = String(fecha.getDate()).padStart(2, '0');
        const hours = String(fecha.getHours()).padStart(2, '0');
        const minutes = String(fecha.getMinutes()).padStart(2, '0');
        const seconds = String(fecha.getSeconds()).padStart(2, '0');
      
        return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    };

    const postPedido = async (pedido) => {
        try{
            const response = await fetch('http://localhost:9080/pedidos', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(pedido),
            });

            if (response.ok) {
                console.log('Pedido registrado con éxito');
            } else {
                console.log('Error al registrar el pedido');
            }
        } catch (error) {
            console.error('Error al registrar el pedido:', error);
        }
    };

    const putProductos = async (producto, id) => {
        try{
            const response = await fetch(`http://localhost:9080/productos/${id}`,{
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(producto),
            });

            if (response.ok) {
                console.log('Producto actualizado con éxito');
            } else {
                console.log('Error al actualizar el producto');
            }
        } catch (error) {
            console.error('Error al actualizar el producto:', error);
        }
    };

    const finalizarVenta = async () => {
        getMaxPedidoId();
        const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));

        const fechaFormateada = formatearFecha(new Date());

        const venta = {
            id_cliente: clienteSeleccionado.id,
            nombre_cliente: clienteSeleccionado.nombre,
            id_pedido: pedidoId+1,
            id_logistica: logisticaSeleccionada.id,
            logistica: logisticaSeleccionada.nombre,
            fecha: fechaFormateada,
            subtotal: subTotal,
            descuento: descuento,
            precio_final_usd: total/1200,
            id_metodo_pago: metodoPagoSeleccionado.id,
            metodo_pago: metodoPagoSeleccionado.nombre,
            precio_final_pesos: total,
            observaciones: observaciones,
        };

        for (let i = 0; i < carrito.length; i++) {
            let pedido = {
                id: pedidoId+1,
                id_producto: carrito[i].id,
                sku: carrito[i].sku,
                nombre: carrito[i].nombre,
                tipo_producto: carrito[i].tipo_producto,
                cantidad: carrito[i].cantidad,
                costo: carrito[i].costo,
                precio_venta: carrito[i].precio_venta,
                precio_sin_iva: carrito[i].precio_sin_iva,
                precio_con_iva: carrito[i].precio_con_iva,
                precio_minorista: carrito[i].precio_minorista,
                precio_mayorista: carrito[i].precio_mayorista,
                precio_venta_minimo: carrito[i].precio_venta_minimo
            }
            await delay(100);
            postPedido(pedido);
        }

        for (let i = 0; i < carrito.length; i++) {
            let id_tipo = 1;
            if (carrito[i].tipo_producto === "Servicios"){
                id_tipo = 2;
            }
            let productoUpdate = {
                sku: carrito[i].sku,
                nombre: carrito[i].nombre,
                id_tipo: id_tipo,
                tipo_producto: carrito[i].tipo_producto,
                stock_minimo: carrito[i].stock_minimo,
                stock_actual: carrito[i].stock_actual - carrito[i].cantidad,
                costo: carrito[i].costo,
                precio_venta: carrito[i].precio_venta,
                precio_sin_iva: carrito[i].precio_sin_iva,
                precio_con_iva: carrito[i].precio_con_iva,
                precio_minorista: carrito[i].precio_minorista,
                precio_mayorista: carrito[i].precio_mayorista,
                precio_venta_minimo: carrito[i].precio_venta_minimo
            }
            await delay(100);
            putProductos(productoUpdate, carrito[i].id);
        };
        
        try {
            await delay(100);
            const response = await fetch('http://localhost:9080/ventas', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(venta),
            });
            if (response.ok) {
                alert('Venta registrada con éxito');
                navigate('/sales');
            } else {
                alert('Error al registrar la venta');
            }
        } catch (error) {
            console.error('Error al finalizar la venta:', error);
        }
    };

    return (
        <div className='w-full h-screen overflow-y-auto relative z-10'>
            <div className="max-w-8xl mx-auto mt-10 p-6 bg-gray-800 rounded-lg h-screen">
                <h2 className="text-2xl font-semibold text-white mb-4">Nueva Venta</h2>

                {/* SKU Input */}
                <h3 className="text-xl text-white">Buscar Producto</h3>
                <div className="mb-4">
                    <input
                    type="text"
                    placeholder="SKU del Producto"
                    value={sku}
                    onChange={(e) => setSku(e.target.value)}
                    className="w-full p-2 rounded bg-gray-700 text-white"
                    />
                    <button onClick={fetchProductoBySku} className="bg-blue-500 p-2 rounded mt-2">
                    Obtener Producto
                    </button>
                </div>

                {/* Producto Table */}
                {producto.length > 0 && (
                    <div className="overflow-x-auto mt-4">
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                            <tr>
                                <th className="border border-gray-700 px-4 py-2">ID</th>
                                <th className="border border-gray-700 px-4 py-2">SKU</th>
                                <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                <th className="border border-gray-700 px-4 py-2">Tipo Producto</th>
                                <th className="border border-gray-700 px-4 py-2">Stock Actual</th>
                                <th className="border border-gray-700 px-4 py-2">Precio Venta</th>
                                <th className="border border-gray-700 px-4 py-2">Precio Venta Mínimo</th>
                                <th className="border border-gray-700 px-4 py-2">Cantidad</th>
                                <th className="border border-gray-700 px-4 py-2">Acciones</th>
                            </tr>
                            </thead>
                            <tbody>
                                {producto.map((p) => (
                                    <motion.tr
                                        key={p.id}
                                    >
                                        <td className="border border-gray-700 px-4 py-2">{p.id}</td>
                                        <td className="border border-gray-700 px-4 py-2">{p.sku}</td>
                                        <td className="border border-gray-700 px-4 py-2">{p.nombre}</td>
                                        <td className="border border-gray-700 px-4 py-2">{p.tipo_producto}</td>
                                        <td className="border border-gray-700 px-4 py-2">{p.stock_actual}</td>
                                        <td className="border border-gray-700 px-4 py-2">${p.precio_venta.toFixed(2)}</td>
                                        <td className="border border-gray-700 px-4 py-2">${p.precio_venta_minimo.toFixed(2)}</td>
                                        <td className="border border-gray-700 px-4 py-2">
                                            <div className="flex items-center">
                                            <button
                                                onClick={() => handleCantidadChange(p.id, (cantidad[p.id] || 1) - 1)}
                                                className="px-2 bg-gray-600 rounded-l"
                                            >
                                            </button>
                                            <input
                                                type="number"
                                                value={cantidad[p.id] || 1}
                                                onChange={(e) =>
                                                handleCantidadChange(p.id, parseInt(e.target.value))
                                                }
                                                className="w-12 text-center bg-gray-700"
                                            />
                                            <button
                                                onClick={() => handleCantidadChange(p.id, (cantidad[p.id] || 1) + 1)}
                                                className="px-2 bg-gray-600 rounded-r"
                                            >
                                            </button>
                                            </div>
                                        </td>
                                        <td className="border border-gray-700 px-4 py-2">
                                        <button
                                            onClick={() => agregarAlCarrito(p, cantidad)}
                                            className="bg-green-500 p-2 rounded"
                                        >
                                            Agregar al Carrito
                                        </button>
                                        </td>
                                    </motion.tr>
                                ))}
                            </tbody>
                        </table>
                    </div>
                )}

                <br />

                {/* CUIT Input */}
                <div className="mb-4">
                    <h3 className="text-xl text-white">Buscar Cliente</h3>
                    <input
                        type="text"
                        placeholder="CUIT del Cliente"
                        onChange={(e) => setCuit(e.target.value)}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                    />
                    <button onClick={verificarCliente} className="bg-blue-500 p-2 rounded mt-2">
                        Buscar Cliente
                    </button>
                </div>

                {/* Cliente Table */}
                {clientes.length > 0 && (
                    <div className="overflow-x-auto mt-4">
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                            <tr>
                                <th className="border border-gray-700 px-4 py-2">ID</th>
                                <th className="border border-gray-700 px-4 py-2">CUIT</th>
                                <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                <th className="border border-gray-700 px-4 py-2">Razon Social</th>
                                <th className="border border-gray-700 px-4 py-2">Telefono</th>
                                <th className="border border-gray-700 px-4 py-2">Email</th>
                                <th className="border border-gray-700 px-4 py-2">Whatsapp</th>
                                <th className="border border-gray-700 px-4 py-2">Acciones</th>
                            </tr>
                            </thead>
                            <tbody>
                                {clientes.map((c) => (
                                    <motion.tr
                                        key={c.id}
                                    >
                                        <td className="border border-gray-700 px-4 py-2">{c.id}</td>
                                        <td className="border border-gray-700 px-4 py-2">{c.cuit}</td>
                                        <td className="border border-gray-700 px-4 py-2">{c.nombre}</td>
                                        <td className="border border-gray-700 px-4 py-2">{c.razon_social}</td>
                                        <td className="border border-gray-700 px-4 py-2">{c.telefono}</td>
                                        <td className="border border-gray-700 px-4 py-2">{c.email}</td>
                                        <td className="border border-gray-700 px-4 py-2">{c.whatsapp}</td>

                                        <td className="border border-gray-700 px-4 py-2">
                                            <button
                                                onClick={() => setClienteSeleccionado(c)}
                                                className="bg-green-500 p-2 rounded"
                                            >
                                                Elegir Cliente
                                            </button>
                                        </td>
                                    </motion.tr>
                                ))}
                            </tbody>
                        </table>
                    </div>
                )}

                <br />

                {/* Input de Descuento */}
                <div className="mb-4 ">
                    <h3 className="text-xl text-white">Descuento</h3>
                    <input
                        type="number"
                        placeholder="Descuento"
                        onChange={(e) => setDescuento(e.target.value)}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                    />
                    <button onClick={aplicarDescuento} className="bg-blue-500 p-2 rounded mt-2">
                        Aplicar Descuento
                    </button>
                </div>

                <br />

                {/* Logistica select */}
                <div className="mb-4">
                    <h3 className="text-xl text-white">Buscar Logistica</h3>
                    <button onClick={getLogistica} className="bg-blue-500 p-2 rounded mt-2">
                        Buscar Logistica
                    </button>
                </div>

                {/* Logistica Table */}
                {logisticas.length > 0 && (
                    <div className="overflow-x-auto mt-4">
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                            <tr>
                                <th className="border border-gray-700 px-4 py-2">ID</th>
                                <th className="border border-gray-700 px-4 py-2">Razon Social</th>
                                <th className="border border-gray-700 px-4 py-2">CUIT</th>
                                <th className="border border-gray-700 px-4 py-2">Direccion</th>
                                <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                <th className="border border-gray-700 px-4 py-2">Telefono</th>
                                <th className="border border-gray-700 px-4 py-2">Tipo</th>
                                <th className="border border-gray-700 px-4 py-2">Acciones</th>
                            </tr>
                            </thead>
                            <tbody>
                                {logisticas.map((l) => (
                                    <motion.tr
                                        key={l.id}
                                    >
                                        <td className="border border-gray-700 px-4 py-2">{l.id}</td>
                                        <td className="border border-gray-700 px-4 py-2">{l.razon_social}</td>
                                        <td className="border border-gray-700 px-4 py-2">{l.cuit}</td>
                                        <td className="border border-gray-700 px-4 py-2">{l.direccion}</td>
                                        <td className="border border-gray-700 px-4 py-2">{l.nombre}</td>
                                        <td className="border border-gray-700 px-4 py-2">{l.telefono}</td>
                                        <td className="border border-gray-700 px-4 py-2">{l.tipo}</td>

                                        <td className="border border-gray-700 px-4 py-2">
                                            <button
                                                onClick={() => setLogisticaSeleccionada(l)}
                                                className="bg-green-500 p-2 rounded"
                                            >
                                                Elegir Logistica
                                            </button>
                                        </td>
                                    </motion.tr>
                                ))}
                            </tbody>
                        </table>
                    </div>
                )}

                <br />

                {/* Metodo de pago select */}
                <div className="mb-4">
                    <h3 className="text-xl text-white">Buscar Metodo de Pago</h3>
                    <button onClick={getMetodoPago} className="bg-blue-500 p-2 rounded mt-2">
                        Buscar metodo de pago
                    </button>
                </div>

                {/* Metodo de pago Table */}
                {metodoPagos.length > 0 && (
                    <div className="overflow-x-auto mt-4">
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                            <tr>
                                <th className="border border-gray-700 px-4 py-2">ID</th>
                                <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                <th className="border border-gray-700 px-4 py-2">Acciones</th>
                            </tr>
                            </thead>
                            <tbody>
                                {metodoPagos.map((mp) => (
                                    <motion.tr
                                        key={mp.id}
                                    >
                                        <td className="border border-gray-700 px-4 py-2">{mp.id}</td>
                                        <td className="border border-gray-700 px-4 py-2">{mp.nombre}</td>

                                        <td className="border border-gray-700 px-4 py-2">
                                            <button
                                                onClick={() => setMetodoPagoSeleccionado(mp)}
                                                className="bg-green-500 p-2 rounded"
                                            >
                                                Elegir Metodo de Pago
                                            </button>
                                        </td>
                                    </motion.tr>
                                ))}
                            </tbody>
                        </table>
                    </div>
                )}

                <br />
                
                {/* Input de Observaciones */}
                <div className="mb-4 ">
                    <h3 className="text-xl text-white">Observaciones</h3>
                    <input
                        type="text"
                        placeholder="Observaciones"
                        onChange={(e) => setObservaciones(e.target.value)}
                        className="w-full p-2 rounded bg-gray-700 text-white"
                    />
                    {/* <button onClick={aplicarDescuento} className="bg-blue-500 p-2 rounded mt-2">
                        Aplicar Descuento
                    </button> */}
                </div>

                <br />
                <ColoredLine color="white" />
                <br />
                <h2 className="text-2xl font-semibold text-white mb-4">Detalles de Venta</h2>

                {/* Carrito Table */}
                {carrito.length > 0 && (
                    <div className="overflow-x-auto mt-8">
                    <h3 className="text-xl text-white mb-4">Productos en el Carrito</h3>
                    <table className="w-full text-white border-collapse border border-gray-700">
                        <thead>
                        <tr>
                            <th className="border border-gray-700 px-4 py-2">ID</th>
                            <th className="border border-gray-700 px-4 py-2">Nombre</th>
                            <th className="border border-gray-700 px-4 py-2">Cantidad</th>
                            <th className="border border-gray-700 px-4 py-2">Precio Unitario</th>
                            <th className="border border-gray-700 px-4 py-2">Total</th>
                        </tr>
                        </thead>
                        <tbody>
                        {carrito.map((item) => (
                            <tr key={item.id}>
                            <td className="border border-gray-700 px-4 py-2">{item.id}</td>
                            <td className="border border-gray-700 px-4 py-2">{item.nombre}</td>
                            <td className="border border-gray-700 px-4 py-2">{item.cantidad}</td>
                            <td className="border border-gray-700 px-4 py-2">${item.precio_venta.toFixed(2)}</td>
                            <td className="border border-gray-700 px-4 py-2">
                                ${(item.cantidad * item.precio_venta).toFixed(2)}
                            </td>
                            </tr>
                        ))}
                        </tbody>
                    </table>
                    </div>
                )}

                {/* Tabla del Cliente Seleccionado */}
                {clienteSeleccionado && (
                    <div className="overflow-x-auto mt-8">
                        <h3 className="text-xl text-white mb-4">Cliente Seleccionado</h3>
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                                <tr>
                                    <th className="border border-gray-700 px-4 py-2">ID</th>
                                    <th className="border border-gray-700 px-4 py-2">CUIT</th>
                                    <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                    <th className="border border-gray-700 px-4 py-2">Razón Social</th>
                                    <th className="border border-gray-700 px-4 py-2">Teléfono</th>
                                    <th className="border border-gray-700 px-4 py-2">Email</th>
                                    <th className="border border-gray-700 px-4 py-2">WhatsApp</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.id}</td>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.cuit}</td>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.nombre}</td>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.razon_social}</td>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.telefono}</td>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.email}</td>
                                    <td className="border border-gray-700 px-4 py-2">{clienteSeleccionado.whatsapp}</td>
                                </tr>
                            </tbody>
                        </table>
                    </div>
                )}

                {/* Tabla del Logistica Seleccionado */}
                {logisticaSeleccionada && (
                    <div className="overflow-x-auto mt-8">
                        <h3 className="text-xl text-white mb-4">Logistica Seleccionado</h3>
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                                <tr>
                                    <th className="border border-gray-700 px-4 py-2">ID</th>
                                    <th className="border border-gray-700 px-4 py-2">Razón Social</th>
                                    <th className="border border-gray-700 px-4 py-2">CUIT</th>
                                    <th className="border border-gray-700 px-4 py-2">Direccion</th>
                                    <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                    <th className="border border-gray-700 px-4 py-2">Teléfono</th>
                                    <th className="border border-gray-700 px-4 py-2">Tipo</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.id}</td>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.razon_social}</td>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.cuit}</td>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.direccion}</td>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.nombre}</td>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.telefono}</td>
                                    <td className="border border-gray-700 px-4 py-2">{logisticaSeleccionada.tipo}</td>
                                </tr>
                            </tbody>
                        </table>
                    </div>
                )}

                {/* Tabla del Metodo de pago Seleccionado */}
                {metodoPagoSeleccionado && (
                    <div className="overflow-x-auto mt-8">
                        <h3 className="text-xl text-white mb-4">Metodo de Pago Seleccionado</h3>
                        <table className="w-full text-white border-collapse border border-gray-700">
                            <thead>
                                <tr>
                                    <th className="border border-gray-700 px-4 py-2">ID</th>
                                    <th className="border border-gray-700 px-4 py-2">Nombre</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <td className="border border-gray-700 px-4 py-2">{metodoPagoSeleccionado.id}</td>
                                    <td className="border border-gray-700 px-4 py-2">{metodoPagoSeleccionado.nombre}</td>
                                </tr>
                            </tbody>
                        </table>
                    </div>
                )}

                <div className="mt-4">
                    <h3 className="text-xl text-white">Observaciones: {observaciones}</h3>
                    <h3 className="text-xl text-white">Subtotal: ${subTotal.toFixed(2)}</h3>
                    <h3 className="text-xl text-white">Descuento: ${descuento}</h3>
                    <h3 className="text-xl text-white">Total: ${total.toFixed(2)}</h3>
                </div>
                <br />
                {/* Botón Finalizar Venta */}
                <div className="mb-4">
                    <button onClick={finalizarVenta} className="bg-green-500 p-2 rounded">
                    Finalizar Venta
                    </button>
                </div>
            </div>
        </div>
    );
};

export default AddSaleForm;
